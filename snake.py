from enum import Enum
import numpy as np

def valid(position, N):
    """Valid if the following things are not true:
    1. has not intersected with the edge, so no x or y = 0 or N
    2. has not intersected with itself, so no tuple is the same as another tuple
    """
    if len([item for item in position[0] if item[0] == -1 or item[0] == N or item[1] == -1 or item[1] == N]) != 0:
        return False
    elif len(position[0]) != len(set(position[0])):
        return False
    return True

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
