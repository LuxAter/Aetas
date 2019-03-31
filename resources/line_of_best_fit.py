import numpy as np

max_epoch=100
pop_size=500

def initializer():
    return list(np.random.rand(2))

def terminator(x):
    return 1 if np.sum(x) > 1.95 else 0

