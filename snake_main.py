#!/usr/bin/python3

from argparse import ArgumentParser

import numpy as np

import snake
import user
import dumbai
import perfectai
import depthai
import ai

def user_input(position, N):
    while True:
        move = input()
        if move == 'w':
            return 0
        elif move == 's':
            return 1
        elif move == 'd':
            return 2
        elif move == 'a':
            return 3
        elif move == 'q':
            return -1
        elif move == 'r':
            print(snake.snake_ray(position, N))

if __name__ == "__main__":
    # print("\033[2J\033[H", end='', flush=True)
    parser = ArgumentParser()
    parser.add_argument(
        "N", nargs='?', type=int, default=20, help="Size of snake grid")
    # parser.add_argument(
    #     "--K", nargs='?', type=int, default=5, help="Size of snake grid")
    args = parser.parse_args()

    print(ai.evaluate(np.random.rand(100).tolist(), args.N, False))

    # snake.snake(args.N, depthai.depth_ai(args.K), True)
    # snake.snake(args.N, user_input, True)
    # snake.snake(args.N, user.input_time, True)
    # snake.snake(args.N, dumbai.dumb_ai, True)
    # snake.snake(args.N, perfectai.perfect_ai, True)
