import numpy as np
import snake
import time


def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))

def relu(x):
    return np.maximum(x, 0.0)


class Network(object):

    def __init__(self, vals, activation, arch):
        self.weights = []
        self.biases = []
        self.activation = activation
        if arch:
            pos = 0
            arch = [12] + arch + [4]
            for i in range(1, len(arch)):
                self.weights.append(
                    np.asarray(vals[pos:pos + (arch[i] * arch[i - 1])]).reshape(
                        arch[i], arch[i - 1]))
                pos += (arch[i] * arch[i - 1])
                self.biases.append(np.asarray(vals[pos:pos + arch[i]]))
                pos += arch[i]
        else:
            self.weights = [np.asarray(vals[:48]).reshape(4, 12)]
            self.biases = [np.asarray(vals[48:])]

    def forward(self, x):
        x = np.asarray([1.0/(i+1.0) for i in x])
        for i in range(len(self.weights)):
            x = self.activation((self.weights[i] @ x) + self.biases[i])
        return x.tolist()


def evaluate(chromosome, arch=[], N=20, display=False, sleep=None, avg=10):

    network = Network(chromosome, relu, arch)

    def get_move(position, N):
        rays = snake.wall_ray(position, N) + snake.snake_ray(
            position, N) + snake.apple_ray(position, N)
        probs = network.forward(rays)
        # print(probs)
        # return probs.index(max(probs))
        return np.random.choice([i for i, x in enumerate(probs) if x == max(probs)])

    score = 0
    for i in range(avg):
        score += snake.snake(N, get_move, -100, display, sleep=sleep)
    return score / avg
