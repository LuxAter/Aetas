import numpy as np
import snake
import time

def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))

class Network(object):
    def __init__(self, vals, activation):
        # print(vals)
        self.weights = np.asarray(vals[:-4]).reshape(4, 24)
        # print(self.weights)
        self.bias = np.asarray(vals[-4:])
        self.activation = activation

    def forward(self, x):
        return ((self.weights @ np.asarray(x)) + self.bias).tolist()
        # return self.activation((self.weights @ np.asarray(x)) + self.bias).tolist()

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
