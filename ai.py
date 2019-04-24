import numpy as np
import snake
import time


def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))


class Network(object):

    def __init__(self, vals, activation):
        self.weights = np.asarray(vals[:48]).reshape(4, 12)
        self.bias = np.asarray(vals[48:])
        # self.weights1 = np.asarray(vals[:336]).reshape(14, 24)
        # self.bias1 = np.asarray(vals[336:350])
        # self.weights2 = np.asarray(vals[350:-4]).reshape(4, 14)
        # self.bias2 = np.asarray(vals[-4:])

    def forward(self, x):
        return ((self.weights @ np.asarray(x)) + self.bias).tolist()
        # return ((self.weights2 @ ((self.weights1 @ np.asarray(x)) + self.bias1))
        #         + self.bias2).tolist()


def evaluate(chromosome, N=20, display=False, sleep=None, avg=10):

    network = Network(chromosome, sigmoid)

    def get_move(position, N):
        rays = snake.wall_ray(position, N) + snake.snake_ray(
            position, N) + snake.apple_ray(position, N)
        probs = network.forward(rays)
        # print(probs)
        return probs.index(max(probs))
        # return np.random.choice([i for i, x in enumerate(probs) if x == max(probs)])

    score = 0
    for i in range(avg):
        score += snake.snake(N, get_move, -100, display, sleep=sleep)
    return score / avg
