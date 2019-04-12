import time

UP = 0
DOWN = 1
RIGHT = 2
LEFT = 3

LOOP_ONE = True

def perfect_ai(position, N):
    global LOOP_ONE
    time.sleep(0.01)
    head = position[0][-1]
    if N % 2 == 0:
        if head == (0, 0):
            return DOWN
        elif head[1] == 0:
            return LEFT
        elif head[1] == 1:
            if head[0] == N-1:
                return UP
            elif head[0] % 2 == 0:
                return DOWN
            return RIGHT
        elif head[1] == N-1:
            if head[0] % 2 == 0:
                return RIGHT
            return UP
        elif head[0] % 2 == 0:
            return DOWN
        return UP
    else:
        if head == (1, 0):
            if LOOP_ONE:
                LOOP_ONE = False
                return DOWN
            else:
                LOOP_ONE = True
                return LEFT
        if LOOP_ONE:
            if head == (0, 0):
                return DOWN
            elif head[1] == 0:
                return LEFT
            elif head[1] == 1:
                if head[0] % 2 == 1 and head[0] == N-2:
                    return UP
                elif head[0] % 2 == 1:
                    return RIGHT
                return DOWN
            elif head[1] == N-1:
                if head[0] % 2 == 0:
                    return RIGHT
                return UP
            if head[0] % 2 == 0:
                return DOWN
            return UP
        elif not LOOP_ONE:
            if head[1] == 0:
                return LEFT
            elif head[1] == 1:
                if head[0] % 2 == 0 and head[0] == N-1:
                    return UP
                elif head[0] % 2 == 0:
                    return RIGHT
                return DOWN
            elif head[1] == N-1:
                if head[0] % 2 == 0:
                    return UP
                return RIGHT
            if head[0] % 2 == 0:
                return UP
            return DOWN

