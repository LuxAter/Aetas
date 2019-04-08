from enum import Enum
import numpy as np


def user_input(position):
    while True:
        move = input()
        if move == 'w':
            return 0
        elif move == 's':
            return 1
        elif move == 'a':
            return 2
        elif move == 'd':
            return 3
        elif move == 'q':
            return -1


def snake(N, get_move):
    position = ([(np.random.randint(1, N - 1), np.random.randint(1, N - 1))],
                (np.random.randint(1, N - 1), np.random.randint(1, N - 1)))
    while (True):
        move = get_move(position)
        position = update(position, move)
        if not valid(position, N):
            break
        draw(position, N)


if __name__ == "__main__":
    snake(20, user_input)
