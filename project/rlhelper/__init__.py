import numpy as np
import random

class RLHelper:
    """
    Classe di utilità per algoritmi di Reinforcement Learning tabellari.
    Fornisce implementazioni statiche di Q-Learning e SARSA per ambienti OpenAI Gym.
    Tutti i metodi sono statici e possono essere usati senza istanziare la classe.
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

# Funzioni standalone per retrocompatibilità

def q_learning(env, alpha=0.1, gamma=0.99, epsilon=0.1, episodes=10000, max_steps=100, verbose=False):
    """
    Wrapper per RLHelper.q_learning per retrocompatibilità.
    Vedi RLHelper.q_learning per la documentazione completa.
    """
    return RLHelper.q_learning(env, alpha, gamma, epsilon, episodes, max_steps, verbose)

def sarsa(env, alpha=0.1, gamma=0.99, epsilon=0.1, episodes=10000, max_steps=100, verbose=False):
    """
    Wrapper per RLHelper.sarsa per retrocompatibilità.
    Vedi RLHelper.sarsa per la documentazione completa.
    """
    return RLHelper.sarsa(env, alpha, gamma, epsilon, episodes, max_steps, verbose)
