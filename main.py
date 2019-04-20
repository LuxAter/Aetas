#!/usr/bin/python3

from argparse import ArgumentParser

import snake
import user
import dumbai
import perfectai
import depthai

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
    print("\033[2J\033[H", end='', flush=True)
    parser = ArgumentParser()
    parser.add_argument(
        "N", nargs='?', type=int, default=20, help="Size of snake grid")
    parser.add_argument(
        "--K", nargs='?', type=int, default=5, help="Size of snake grid")
    args = parser.parse_args()
    # snake.snake(args.N, depthai.depth_ai(args.K))
    snake.snake(args.N, user_input)
    # snake.snake(args.N, user.input_time)
    # snake.snake(args.N, dumbai.dumb_ai)
    # snake.snake(args.N, perfectai.perfect_ai)
