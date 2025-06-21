import numpy as np
import random
import torch
import torch.nn as nn
import torch.optim as optim
from collections import deque

class RLHelper:
    """
    Utility class for tabular and neural network-based Reinforcement Learning algorithms.
    Provides static implementations of Q-Learning, SARSA, Dyna-Q, DDQN and others for OpenAI Gym environments.
    """

    # INTERNAL METHODS

    @staticmethod
    def _select_action(state, epsilon, n_actions, online_net, device):
        """
        Epsilon-greedy action selection for DDQN.

        Args:
            state (np.ndarray): Current state.
            epsilon (float): Exploration rate.
            n_actions (int): Number of possible actions.
            online_net (nn.Module): Online Q-network.
            device (torch.device): Device to use.
        Returns:
            int: Selected action.
        """
        if random.random() > epsilon:
            with torch.no_grad():
                state = torch.FloatTensor(state).unsqueeze(0).to(device)
                return online_net(state).argmax(1).item()
        else:
            return random.randrange(n_actions)

    @staticmethod
    def _optimize_model(online_dqn, target_dqn, memory, optimizer, batch_size, gamma, device):
        """
        Perform a single optimization step for the online network using DDQN logic.

        Args:
            online_dqn (nn.Module): Online Q-network.
            target_dqn (nn.Module): Target Q-network.
            memory (ReplayBuffer): Experience replay buffer.
            optimizer (torch.optim.Optimizer): Optimizer for the online network.
            batch_size (int): Batch size for optimization.
            gamma (float): Discount factor.
            device (torch.device): Device to use.
        """
        if len(memory) < batch_size:
            return

        state, action, reward, next_state, done = memory.sample(batch_size)

        state = torch.FloatTensor(state).to(device)
        action = torch.LongTensor(action).to(device)
        reward = torch.FloatTensor(reward).to(device)
        next_state = torch.FloatTensor(next_state).to(device)
        done = torch.FloatTensor(done).to(device)

        q_value = online_dqn(state).gather(1, action.unsqueeze(1)).squeeze(1)
        next_actions = online_dqn(next_state).argmax(1).unsqueeze(1)
        next_q_value = target_dqn(next_state).gather(1, next_actions).squeeze(1)
        expected_q_value = reward + gamma * next_q_value * (1 - done)

        loss = (q_value - expected_q_value.detach()).pow(2).mean()

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    # END INTERNAL METHODS

    # APIs

    @staticmethod
    def q_learning(env, alpha=0.1, gamma=0.99, epsilon=0.1, episodes=10000, max_steps=100, verbose=False):
        """
        Q-Learning algorithm for discrete environments.

        Args:
            env: Gymnasium/OpenAI Gym environment with discrete spaces.
            alpha (float): Learning rate.
            gamma (float): Discount factor.
            epsilon (float): Initial exploration rate.
            episodes (int): Number of training episodes.
            max_steps (int): Maximum number of steps per episode.
            verbose (bool): If True, print information during learning.
        Returns:
            Q (np.ndarray): Learned Q-table.
            policy (np.ndarray): Policy derived from the Q-table.
        """
        n_states = env.observation_space.n
        n_actions = env.action_space.n
        Q = np.zeros((n_states, n_actions))

        for episode in range(episodes):
            epsilon = max(0.01, epsilon - 0.01)
            state = env.reset()[0]

            for step in range(max_steps):

                if random.uniform(0, 1) < epsilon:
                    action = env.action_space.sample()
                else:
                    action = np.argmax(Q[state, :])

                next_state, reward, done, _, _ = env.step(action)

                if done and reward <= 0:
                    reward = -1
                if state == next_state:
                    reward -= 0.1

                best_next_action = np.argmax(Q[next_state, :])
                td_target = reward + gamma * Q[next_state, best_next_action]
                td_error = td_target - Q[state, action]
                Q[state, action] += alpha * td_error

                state = next_state

                if done:
                    if verbose:
                        print(f"Episode {episode} finished after {step+1} steps")
                    break

        policy = np.argmax(Q, axis=1)
        return Q, policy

    @staticmethod
    def sarsa(env, alpha=0.1, gamma=0.99, epsilon=0.1, episodes=10000, max_steps=100, verbose=False):
        """
        SARSA algorithm for discrete environments.

        Args:
            env: Gymnasium/OpenAI Gym environment with discrete spaces.
            alpha (float): Learning rate.
            gamma (float): Discount factor.
            epsilon (float): Initial exploration rate.
            episodes (int): Number of training episodes.
            max_steps (int): Maximum number of steps per episode.
            verbose (bool): If True, print information during learning.
        Returns:
            Q (np.ndarray): Learned Q-table.
            policy (np.ndarray): Policy derived from the Q-table.
        """
        n_states = env.observation_space.n
        n_actions = env.action_space.n
        Q = np.zeros((n_states, n_actions))

        for episode in range(episodes):

            epsilon = max(0.01, epsilon - 0.01)
            state = env.reset()[0]

            if random.uniform(0, 1) < epsilon:
                action = env.action_space.sample()
            else:
                action = np.argmax(Q[state, :])

            for step in range(max_steps):
                next_state, reward, done, _, _ = env.step(action)

                if done and reward <= 0:
                    reward = -1
                if state == next_state:
                    reward -= 0.1

                if random.uniform(0, 1) < epsilon:
                    next_action = env.action_space.sample()
                else:
                    next_action = np.argmax(Q[next_state, :])

                td_target = reward + gamma * Q[next_state, next_action]
                td_error = td_target - Q[state, action]
                Q[state, action] += alpha * td_error

                if verbose:
                    print(f"Episode = {episode}, state={state}, action={action}, reward={reward}, done={done}")

                state = next_state
                action = next_action

                if done:
                    break

        policy = np.argmax(Q, axis=1)
        return Q, policy

    @staticmethod
    def dyna_q(env, alpha=0.1, gamma=0.99, epsilon=0.1, episodes=1000, planning=10):
        """
        Dyna-Q algorithm for discrete tabular environments.
        Combines direct learning from the environment and planning using a model.

        Args:
            env: Gymnasium/OpenAI Gym environment with discrete spaces.
            alpha (float): Learning rate.
            gamma (float): Discount factor.
            epsilon (float): Initial exploration rate.
            episodes (int): Number of training episodes.
            planning (int): Number of planning steps per real step.
        Returns:
            Q (np.ndarray): Learned Q-table.
            model (dict): Model of observed transitions {(state, action): (reward, next_state)}.
            policy (np.ndarray): Policy derived from the Q-table.
        """
        n_states = env.observation_space.n
        n_current_actions = env.current_action_space.n
        Q = np.zeros((n_states, n_current_actions))
        model = {}

        for episode in range(episodes):
            done = False
            epsilon = max(0.01, epsilon - 0.01)
            state = env.reset()[0]

            while not done:

                if random.uniform(0, 1) < epsilon:
                    current_action = env.current_action_space.sample()
                else:
                    current_action = np.argmax(Q[state, :])

                next_state, reward, done, _, _ = env.step(current_action)
                model[(state, current_action)] = (reward, next_state)

                if random.uniform(0, 1) < epsilon:
                    next_action = env.current_action_space.sample()
                else:
                    next_action = np.argmax(Q[next_state, :])

                td_target = reward + gamma * Q[next_state, next_action]
                td_error = td_target - Q[state, current_action]
                Q[state, current_action] += alpha * td_error

                for _ in range(planning):
                    if not model:
                        break
                    s, a = random.choice(list(model.keys()))
                    r, s_prime = model[(s, a)]
                    a_prime = np.argmax(Q[s_prime, :])
                    td_target = r + gamma * Q[s_prime, a_prime]
                    td_error = td_target - Q[s, a]
                    Q[s, a] += alpha * td_error

                state = next_state

        policy = np.argmax(Q, axis=1)
        return Q, model, policy

    @staticmethod
    def ddqn(env, dqn_class, episodes=300, batch_size=64, gamma=0.99, epsilon_start=1.0, epsilon_end=0.1, epsilon_decay=1000, lr=0.0003, target_update=1000, memory_size=100000, device=None, max_steps=1000, verbose=False):
        """
        Double Deep Q-Network (DDQN) algorithm for discrete environments.

        Args:
            env: OpenAI Gym environment.
            dqn_class: Class of the DQN network (must be compatible with PyTorch nn.Module).
            episodes (int): Number of training episodes.
            batch_size (int): Batch size for optimization.
            gamma (float): Discount factor.
            epsilon_start (float): Initial epsilon for exploration.
            epsilon_end (float): Final epsilon value.
            epsilon_decay (int): Number of steps to decay epsilon.
            lr (float): Learning rate.
            target_update (int): Number of episodes between target network updates.
            memory_size (int): Replay buffer size.
            device: PyTorch device.
            max_steps (int): Max steps per episode.
            verbose (bool): If True, print progress.
        Returns:
            list: Rewards per episode.
        """
        if device is None:
            device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        input_shape = env.observation_space.shape[0]
        num_actions = env.action_space.n
        online_net = dqn_class(input_shape, num_actions).to(device)
        target_net = dqn_class(input_shape, num_actions).to(device)
        target_net.load_state_dict(online_net.state_dict())
        optimizer = optim.Adam(online_net.parameters(), lr=lr)
        memory = ReplayBuffer(memory_size)
        epsilon = epsilon_start
        epsilon_decay_step = (epsilon_start - epsilon_end) / epsilon_decay
        episode_rewards = []

        for episode in range(episodes):
            state, _ = env.reset()
            total_reward = 0

            for t in range(max_steps):
                action = RLHelper._select_action(state, epsilon, num_actions, online_net, device)
                next_state, reward, done, _, _ = env.step(action)

                if done and reward <= 0:
                    reward = -1
                total_reward += reward
                memory.push(state, action, reward, next_state, done)
                state = next_state
                RLHelper._optimize_model(online_net, target_net, memory, optimizer, batch_size, gamma, device)
                if done:
                    break
                epsilon = max(epsilon_end, epsilon - epsilon_decay_step)

            if episode % target_update == 0:
                target_net.load_state_dict(online_net.state_dict())
            episode_rewards.append(total_reward)
            if verbose:
                print(f"Episode {episode+1}, Total reward: {total_reward}")

        return episode_rewards

    # END APIs

class ReplayBuffer:
    """
    Replay buffer for storing transitions during DDQN training.
    """

    def __init__(self, max_size=100000):
        self.memory = deque(maxlen=max_size)

    def push(self, *args):
        """
        Add a transition to the memory.
        """
        self.memory.append(args)

    def sample(self, batch_size):
        """
        Randomly sample a batch of transitions from memory.
        """
        batch = random.sample(self.memory, batch_size)
        return [np.array(x) for x in zip(*batch)]

    def __len__(self):
        """
        Return the number of transitions in memory.
        """
        return len(self.memory)
