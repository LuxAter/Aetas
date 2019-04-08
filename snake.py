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

def draw(position, N):
    print("\u250f{}\u2513".format("\u2501" * (N*2)))
    for i in range(N):
        row = ['  '] * N
        for seg in position[0]:
            if seg[1] == i:
                row[seg[0]] = '\u2588\u2588'
        if position[1][1] == i:
            row[position[1][0]] = '\033[32m\u2588\u2588\033[0m'
        print("\u2503{}\u2503".format(''.join(row)))
    print("\u2517{}\u251B".format("\u2501" * (N*2)))
    print("\033[H",end='',flush=True)


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
    position = [[(np.random.randint(1, N - 1), np.random.randint(1, N - 1))],
                (np.random.randint(1, N - 1), np.random.randint(1, N - 1))]
    while (True):
        draw(position, N)
        move = get_move(position)
        if move < 0:
            break
        position = update(position, move)
        if not valid(position, N):
            break


if __name__ == "__main__":
    print("\033[2J\033[H")
    snake(20, user_input)
