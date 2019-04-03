#!/usr/bin/python3

from os.path import isdir
import numpy as np
import matplotlib.pyplot as plt
from random import shuffle
import random

from pprint import pprint


def sort_by_fitness(pop, fitness):
    """Sorts population based by the value of fitness, meaning our most fit is
    at the begining, and the least fit is at the end."""
    fitness, pop = zip(*sorted(zip(fitness, pop)))
    return list(pop), list(fitness)


def plot_best(generation, pop, fitness, plot_n=1):
    """Givin the current generation, the population, and fitness. This will
    plot the best plot_n from the population, and saves it in a file."""
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


def initialize(n_pop, n_points):
    return [np.random.rand(2 * n_points) for i in range(n_pop)]


def evaluate(pop):
    """Evaluates the fitness of the population, calculating the total path
    distance for the specified chromosome."""
    return [(np.sqrt(ch[0]**2 + ch[1]**2) + np.sum([
        np.sqrt((ch[i] - ch[i + 2])**2 + (ch[i + 1] - ch[i + 3])**2)
        for i in range(0,
                       len(ch) - 2, 2)
    ]) + np.sqrt((ch[-2] - 1)**2 + (ch[-1] - 1)**2))
            for ch in pop]


def terminate(fitness, tolerance):
    """Terminate process if reach total distance withing tolerance level of
    error from a straight line --> sqrt(2).
    """
    for i in fitness:
        if abs((2**(1.0 / 2)) - i) < tolerance:
            return True
    return False

def selection(pop, fitness, n_keep):
    """Selects len(pop)-n_keep from the population utilized the roulette wheel
    selection algorithm. Each chromosome is given a probability proportional to
    the inverse of its fitness. Then using those probabilities a new population
    is selected."""
    total_fit = sum([1.0/x for x in fitness])
    prob = []
    cumulative = 0.0
    for f in fitness:
        cumulative += ((1.0/f) / total_fit)
        prob.append(cumulative)
    new_pop = []
    for i in range(len(pop) - n_keep):
        r = np.random.rand()
        j = 0
        for j in range(len(prob)):
            if prob[j] >= r:
                break
        new_pop.append(pop[j])
    return new_pop



def crossover(new_pop, k):
    """Performs 2-fold crossover on the new population.
    First, shuffles  population to create random parents to go down list.
    Repeats the following len(new_pop) times:
    1. Choose k random numbers in range of points
    2. Sort the points and perform crossover in their order for each fold
    """
    shuffle(new_pop)
    for i in range(len(new_pop) // 2):
        points = random.sample(range(1, len(new_pop[i])), k)
        points.sort()
        for fold in range(k):
            x = points[fold]
            tmp = new_pop[2 * i][:x].copy()
            new_pop[2 * i][:x], new_pop[2 * i + 1][:x] = new_pop[2 * i +
                                                                 1][:x], tmp
    return new_pop

def mutate(new_pop,prob_m,gene_m):
    pop = [np.copy(chrom) for chrom in new_pop]
    for chrom in pop:
        if random.random() < prob_m:
            for i in range(len(chrom)):
                if random.random() < gene_m:
                    chrom[i] = random.random()
    return pop

def replace(pop,fitness,new_pop,n_keep):
    pop, fitness = sort_by_fitness(pop,fitness)
    return pop[:n_keep]+new_pop

def main():
    n_pop = 100
    n_points = 10
    n_keep = 10
    prob_m = 0.4
    gene_m = 0.1
    tolerance = .001
    k = 2
    pop = initialize(n_pop, n_points)
    for gen in range(100):
        fitness = evaluate(pop)
        print(fitness)
        print(len(fitness))
        print("GEN: {:5} FIT: {}".format(gen, min(fitness)))
        plot_best(gen, pop, fitness, 3)
        if terminate(fitness, tolerance):
            break
        new_pop = selection(pop, fitness, n_keep)
        new_pop = crossover(new_pop, k)
        new_pop = mutate(new_pop, prob_m, gene_m)
        pop = replace(pop, fitness, new_pop, n_keep)
        print(pop)
        print(len(pop))

    print(max(fitness))


if __name__ == "__main__":
    main()
