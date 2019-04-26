#!/usr/bin/env python3
from snake import *

import numpy as np
import time
import copy

N = 10


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
            print(apple_ray(position, N))


def get_vec_in(position):
        rays = [1 if x < N**2 else 0 for x in apple_ray(position, N)] + [1/(x+1) for x in wall_ray(position, N)] + [1/(x+1) for x in snake_ray(position, N)]
        return np.asarray(rays)

def snake2(N, get_move, W, max_turn = 0, display=False, sleep=None):
    score = 0
    turn = 0
    length = 1
    position = [[(N //2, N//2)],
                (np.random.randint(1, N - 1), np.random.randint(1, N - 1))]
    for i in range(3):
        position[0].append(position[0][0])
    # position = [[(np.random.randint(1, N - 1), np.random.randint(1, N - 1))],
    #             (np.random.randint(1, N - 1), np.random.randint(1, N - 1))]
    while (True):
        if sleep:
            time.sleep(sleep)
        if display:
            draw(position, N)
        move = get_move(position, N)
        if move < 0:
            break
        prev_len = len(position[0])
        pos_copy = copy.deepcopy(position)
        position = update(position, move, N)
        if prev_len != len(position[0]):
            apple_stuff(pos_copy,W)
        if max_turn < 0 and len(position[0]) != length:
            length = len(position[0])
            turn = -1
        if not valid(position, N):
            break
        turn += 1
        if max_turn > 0 and turn >= max_turn:
            break
        if max_turn < 0 and turn >= abs(max_turn):
            break
    return pos_copy #return losing position


if __name__ == "__main__":
    
    #randomize weights
    num_games = 1 
#for i in range(num_games):
    #intialize game
#losing_pos = snake2(N,user_input,100,True,0)

    ########
#    weights = np.array(
#          [[0.6, 0, 0, 0, -1.3, 0, 0, 0, -1.3, 0, 0.5, 0],
#           [0, 0, 0.6, 0, 0, 0, -1.3, 0, 0.5, 0, -1.3, 0],
#           [0, 0.6, 0, 0, 0, -1.3, 0, 0, 0, -1.3, 0, 0.5],
#           [0, 0, 0, 0.6, 0, 0, 0, -1.3, 0, 0.5, 0, -1.3]])
#weights = np.random.rand(4,12)
    weights = np.zeros((4,12))
    print(weights)

    def net_move(position,N):
        inp = get_vec_in(position)
        probs = np.matmul(weights,inp)
        return np.random.choice([i for i, x in enumerate(probs) if x == max(probs)])

    def apple_stuff(apple_pos,weights):
        apple_move = np.zeros(4)
        index = net_move(apple_pos,N)
        apple_move[index] = 1
        apple_inp = get_vec_in(apple_pos)
        M = np.asmatrix(apple_move)
        I = np.asmatrix(apple_inp)
        weights += 0.05*M.T@I

    #######
    for i in range(10000):
        if i%100 == 0:
            losing_pos = snake2(N,net_move,weights,100,True,0.1)
        else:
            losing_pos = snake2(N,net_move,weights,100,False,0)
        #vec:t
        losing_move = np.zeros(4)
        index = net_move(losing_pos,N)
        losing_move[index] = 1
        losing_inp = get_vec_in(losing_pos)

        M = np.asmatrix(losing_move)
        I = np.asmatrix(losing_inp)

        #test = losing_move@losing_inp
        weights -= 0.1*M.T@I



