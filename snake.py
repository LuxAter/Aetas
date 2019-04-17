#!/usr/bin/python3


from enum import Enum
from argparse import ArgumentParser
import numpy as np

import copy
import user
import dumbai
import perfectai



def get_pref(position, num_steps, N):
    return [take_step(update(position,move,N),num_steps-1,N) for move in range(4)]


#TODO: make insentive for apple
def take_step(position, num_steps,N):
    if not valid(position,N):
        return 0
    elif num_steps == 0:
        return 1
    weights = [take_step(update(position,move,N),num_steps-1,N) for move in range(4)]
    return np.sum(weights)/4


def valid(position, N):
    """Valid if the following things are not true:
    1. has not intersected with the edge, so no x or y = 0 or N
    2. has not intersected with itself, so no tuple is the same as another tuple
    """
    if len([
            item for item in position[0]
            if item[0] == -1 or item[0] == N or item[1] == -1 or item[1] == N
    ]) != 0:
        return False
    elif len(position[0]) != len(set(position[0])):
        return False
    return True


def update(position, move, N):
    apple = copy.deepcopy(position[1])
    snake = copy.deepcopy(position[0])
    new_square = [snake[-1][0], snake[-1][1]]
    if move == 0:
        new_square[1] -= 1
    if move == 1:
        new_square[1] += 1
    if move == 2:
        new_square[0] += 1
    if move == 3:
        new_square[0] -= 1
    new_square = tuple(new_square)
    snake.append(new_square)
    if (new_square == apple):
        apple = (np.random.randint(1, N - 1), np.random.randint(1, N - 1))
        while apple in snake:
            apple = (np.random.randint(1, N - 1), np.random.randint(1, N - 1))
    else:
        snake.pop(0)
    return (snake, apple)


def draw(position, N):
    print("\u250f{}\u2513".format("\u2501" * (N * 2)))
    for i in range(N):
        row = ['  '] * N
        for seg in position[0]:
            if seg[1] == i:
                row[seg[0]] = '\u2588\u2588'
        if position[1][1] == i:
            row[position[1][0]] = '\033[32m\u2588\u2588\033[0m'
        print("\u2503{}\u2503".format(''.join(row)))
    print("\u2517{}\u251B".format("\u2501" * (N * 2)))
    print("\033[H", end='', flush=True)


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
        elif move == 'm':
            print(get_pref(position,2,N))


def init(N):
    return [[(np.random.randint(1, N - 1), np.random.randint(1, N - 1))],
            (np.random.randint(1, N - 1), np.random.randint(1, N - 1))]


def snake(N, get_move):
    position = [[(np.random.randint(1, N - 1), np.random.randint(1, N - 1))],
                (np.random.randint(1, N - 1), np.random.randint(1, N - 1))]
    while (True):
        draw(position, N)
        move = get_move(position, N)
        if move < 0:
            break
        position = update(position, move, N)
        if not valid(position, N):
            break


if __name__ == "__main__":
    print("\033[2J\033[H", end='', flush=True)
    parser = ArgumentParser()
    parser.add_argument(
        "N", nargs='?', type=int, default=20, help="Size of snake grid")
    args = parser.parse_args()
    snake(args.N, user_input)
    #snake(args.N, user.input_time)
    #snake(args.N, dumbai.dumb_ai)
    #snake(args.N, perfectai.perfect_ai)
