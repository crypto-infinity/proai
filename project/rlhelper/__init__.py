import numpy as np
import random

class RLHelper:
    """
    Classe di utilità per algoritmi di Reinforcement Learning tabellari.
    Fornisce implementazioni statiche di Q-Learning, SARSA, Dyna-Q e altri per ambienti OpenAI Gym.
    """

    @staticmethod
    def q_learning(env, alpha=0.1, gamma=0.99, epsilon=0.1, episodes=10000, max_steps=100, verbose=False):
        """
        Algoritmo Q-Learning per ambienti discreti.

        Args:
            env: ambiente Gymnasium/OpenAI Gym con spazi discreti.
            alpha (float): learning rate.
            gamma (float): fattore di sconto.
            epsilon (float): tasso di esplorazione iniziale.
            episodes (int): numero di episodi di training.
            max_steps (int): massimo numero di step per episodio.
            verbose (bool): se True stampa informazioni durante l'apprendimento.

        Returns:
            Q (np.ndarray): tabella Q appresa.
            policy (np.ndarray): politica derivata dalla Q-table.
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
        Algoritmo SARSA per ambienti discreti.

        Args:
            env: ambiente Gymnasium/OpenAI Gym con spazi discreti.
            alpha (float): learning rate.
            gamma (float): fattore di sconto.
            epsilon (float): tasso di esplorazione iniziale.
            episodes (int): numero di episodi di training.
            max_steps (int): massimo numero di step per episodio.
            verbose (bool): se True stampa informazioni durante l'apprendimento.

        Returns:
            Q (np.ndarray): tabella Q appresa.
            policy (np.ndarray): politica derivata dalla Q-table.
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
        Algoritmo Dyna-Q per ambienti discreti tabellari.

        Combina apprendimento diretto dall'ambiente e pianificazione tramite modello.

        Args:
            env: ambiente Gymnasium/OpenAI Gym con spazi discreti.
            alpha (float): learning rate.
            gamma (float): fattore di sconto.
            epsilon (float): tasso di esplorazione iniziale.
            episodes (int): numero di episodi di training.
            planning (int): numero di step di pianificazione per ogni step reale.

        Returns:
            Q (np.ndarray): tabella Q appresa.
            model (dict): modello delle transizioni osservate {(stato, azione): (reward, next_state)}.
            policy (np.ndarray): politica derivata dalla Q-table.
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
