import matplotlib.pyplot as plt
import numpy as np

def smooth(y, box_pts):
    box = np.ones(box_pts)/box_pts
    y = ([y[0]] * box_pts) + y + ([y[-1]] * box_pts)
    y_smooth = np.convolve(y, box, mode='same')
    return y_smooth[box_pts:-box_pts]

def plot_fitness(filename, fitness, smoothed=True):
    plt.plot(fitness)
    if smoothed:
        plt.plot(smooth(fitness, 25))
    # plt.ylim((min(fitness) - 10, max(fitness) + 10))
    plt.savefig(filename, dpi=300, figsize=(40, 30))
