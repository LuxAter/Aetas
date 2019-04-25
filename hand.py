#!/usr/bin/env python3
import numpy as np
import snake
import time


def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))

def relu(x):
    return x
    # return np.maximum(x, 0.0)


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
        x = np.asarray(x[:4] + [1.0/(i+1.0) for i in x[4:]])
        # print(x.tolist())
        for i in range(len(self.weights)):
            x = self.activation((self.weights[i] @ x) + self.biases[i])
        return x.tolist()


if __name__ == "__main__":
    arch = []
    # Pretty Good
    # chromosome = [
    #         10, 0, 0, 0, -1, 0.5, 0, 0, -5, 0, 0.5, 0,
    #         0, 0, 10, 0, 0, 0, -1, 0.5, 0.5, 0, -5, 0,
    #         0, 10, 0, 0, 0, -1, 0.5, 0, 0, -5, 0, 0.5,
    #         0, 0, 0, 10, 0.5, 0, 0, -1, 0, 0.5, 0, -5, 0.25, 0, 0, 0]
    chromosome = [
            0.6, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0.6, 0,
            0, 0, 0.6, 0, 0, 0, -1, 0, 0.6, 0, -1, 0,
            0, 0.6, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0.6,
            0, 0, 0, 0.6, 0, 0, 0, -1, 0, 0.6, 0, -1, 0, 0, 0, 0]
    network = Network(chromosome, relu, arch)

    def get_move(position, N):
        rays = [1 if x < 400 else 0 for x in snake.apple_ray(position, N)] + snake.wall_ray(
                position, N) + snake.snake_ray(position, N)
        probs = network.forward(rays)
        # print(probs)
        # return probs.index(max(probs))
        # print(probs)
        # print([i for i, x in enumerate(probs) if x == max(probs)])
        return np.random.choice([i for i, x in enumerate(probs) if x == max(probs)])

    score = 0
    score += snake.snake(20, get_move, -100, True, sleep=0.01)
