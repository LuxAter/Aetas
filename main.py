#!/usr/bin/python3

from os.path import isdir
import numpy as np
import matplotlib.pyplot as plt

from pprint import pprint


def initialize(n_pop, n_points):
    return [np.random.rand(2 * n_points) for i in range(n_pop)]


def sort_by_fitness(pop, fitness):
    fitness, pop = zip(*sorted(zip(fitness, pop)))
    return pop, fitness


def plot_best(generation, pop, fitness, plot_n=1):
    if not isdir("img"):
        return
    pop, fitness = sort_by_fitness(pop, fitness)
    fig = plt.figure(frameon=False)
    fig.set_size_inches(5, 5)
    ax = plt.Axes(fig, [0., 0., 1., 1.])
    ax.set_xlim(-0.05, 1.05)
    ax.set_ylim(-0.05, 1.05)
    ax.set_axis_off()
    fig.add_axes(ax)
    for i in range(plot_n):
        X = [0] + [pop[i][j] for j in range(0, len(pop[i]), 2)] + [1]
        Y = [0] + [pop[i][j] for j in range(1, len(pop[i]), 2)] + [1]
        ax.plot(X, Y)
    ax.plot([0, 1], [0, 1], 'k.')
    fig.savefig("img/{}.png".format(generation), dpi=200)


def evaluate(pop):
    return [(np.sqrt(ch[0]**2 + ch[1]**2) + np.sum([
        np.sqrt((ch[i] - ch[i + 2])**2 + (ch[i + 1] - ch[i + 3])**2)
        for i in range(0,
                       len(ch) - 2, 2)
    ]) + np.sqrt((ch[-2] - 1)**2 + (ch[-1] - 1)**2))
            for ch in pop]


def main():
    n_pop = 100
    n_points = 10
    n_keep = 10
    prob_m = 0.2
    pop = initialize(n_pop, n_points)
    for gen in range(100):
        fitness = evaluate(pop)
        print("GEN: {:5} FIT: {}".format(gen, min(fitness)))
        plot_best(gen, pop, fitness, 3)
        if terminate(fitness):
            break
        new_pop = selection(pop, fitness, n_keep)
        new_pop = crossover(new_pop, k)
        new_pop = mutate(new_pop, prob_m)
        pop = replace(pop, fitness, new_pop, n_keep)
    print(max(fitness))


if __name__ == "__main__":
    main()
