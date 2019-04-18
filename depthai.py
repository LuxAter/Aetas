import numpy as np
import time

import snake

def depth_ai(K=2):
    def get_input(position, N):
        time.sleep(0.005)
        prefs = snake.get_pref(position, K, N)
        choices = []
        for i, x in enumerate(prefs):
            if x == max(prefs):
                choices.append(i)
        # return prefs.index(max(prefs))
        # choices = [i for x, i in enumerate(prefs) if x == max(prefs)]
        # print(choices, max(prefs), prefs)
        return np.random.choice(choices)
    return get_input
