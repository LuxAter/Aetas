#!/usr/bin/python3

import random
import time
from os.path import isdir
from random import shuffle
from argparse import ArgumentParser
from pprint import pprint
from multiprocessing import Pool
import numpy as np
import matplotlib.pyplot as plt

import ai


def sort_by_fitness(pop, fitness):
    """Sorts population based by the value of fitness, meaning our most fit is
    at the begining, and the least fit is at the end."""
    data = list(zip(fitness, pop))
    fitness, pop = zip(*sorted(data, key=lambda x: x[0], reverse=True))
    return list(pop), list(fitness)

def initialize(n_pop):
    return [np.random.rand(100) for i in range(n_pop)]


def evaluate(pop):
    """Evaluates the fitness of the population, calculating the total path
    distance for the specified chromosome."""
    fitnesses = [0] * len(pop)
    with Pool(8) as p:
        fitness = p.map(ai.evaluate, pop)
    return fitness


def terminate(fitness, tolerance):
    """Terminate process if reach total distance withing tolerance level of
    error from a straight line --> sqrt(2).
    """
    # for i in fitness:
    #     if abs((2**(1.0 / 2)) - i) < tolerance:
    #         return True
    return False


def selection(pop, fitness, n_keep):
    """Selects len(pop)-n_keep from the population utilized the roulette wheel
    selection algorithm. Each chromosome is given a probability proportional to
    the inverse of its fitness. Then using those probabilities a new population
    is selected."""
    total_fit = sum([1.0 / x for x in fitness])
    prob = []
    cumulative = 0.0
    for f in fitness:
        cumulative += ((1.0 / f) / total_fit)
        prob.append(cumulative)
    new_pop = []
    for i in range(len(pop) - n_keep):
        r = np.random.rand()
        for j in range(len(prob)):
            if prob[j] >= r:
                new_pop.append(pop[j])
                break
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


def mutate(new_pop, prob_m, gene_m):
    pop = [np.copy(chrom) for chrom in new_pop]
    for chrom in pop:
        if random.random() < prob_m:
            for i in range(len(chrom)):
                if random.random() < gene_m:
                    chrom[i] = chrom[i] + 0.1 - 0.2 * random.random()
                    # chrom[i] = random.random()
    return pop


def replace(pop, fitness, new_pop, n_keep):
    pop, fitness = sort_by_fitness(pop, fitness)
    return pop[:n_keep] + new_pop


def time_exec(should_time, func, *argv):
    if should_time:
        start = time.time()
    ret = func(*argv)
    if should_time:
        return time.time() - start, ret
    return 0, ret


def main():
    parser = ArgumentParser('Genetic')
    parser.add_argument('--N', type=int, default=50, help='Snake grid size')
    parser.add_argument('--pop', type=int, default=100, help='Population size')
    parser.add_argument(
        '--keep',
        type=int,
        default=10,
        help='Number of chromosomes to keep between generations')
    parser.add_argument(
        '--probm',
        type=float,
        default=0.5,
        help='Probability to mutate a chromosome')
    parser.add_argument(
        '--probg', type=float, default=0.1, help='Probability to mutate a gene')
    parser.add_argument('--kpoint', type=int, default=2, help='k-point')
    parser.add_argument(
        '--tol',
        type=float,
        default=0.001,
        help='Tolerance to satisfy before termination')
    parser.add_argument(
        '--no-print',
        action='store_true',
        help='Prevent printing durring evaluation')
    parser.add_argument(
        '--time', action='store_true', help='Time each function')
    parser.add_argument(
        '--epoch', type=int, default=10, help='Generations per epoch')
    parser.add_argument(
        '--max-gen',
        type=int,
        default=1000,
        help='Maximum number of generations')
    parser.add_argument(
        '--save',
        action='store_true',
        help='Saves the top average fitness for each generation')
    args = parser.parse_args()
    n_pop = args.pop
    n_keep = args.keep
    prob_m = args.probm
    gene_m = args.probg
    tolerance = args.tol
    k = args.kpoint
    times = [0, [], [], [], [], [], []]
    averages = []
    times[0], pop = time_exec(args.time, initialize, n_pop)
    gen = 0
    for gen in range(args.max_gen):
        tmp, fitness = time_exec(args.time, evaluate, pop)
        if args.save:
            pop, fitness = sort_by_fitness(pop, fitness)
            averages.append(np.average(fitness[:5]))
        times[1].append(tmp)
        if gen % args.epoch == 0:
            if not args.no_print:
                print("GEN: {:5} FIT: {}".format(gen, max(fitness)))
        if terminate(fitness, tolerance):
            break
        pop_copy = [np.copy(chrom) for chrom in pop]
        tmp, new_pop = time_exec(args.time, selection, pop_copy, fitness,
                                 n_keep)
        times[2].append(tmp)
        tmp, new_pop = time_exec(args.time, crossover, new_pop, k)
        times[3].append(tmp)
        tmp, new_pop = time_exec(args.time, mutate, new_pop, prob_m, gene_m)
        times[4].append(tmp)
        tmp, pop = time_exec(args.time, replace, pop, fitness, new_pop, n_keep)
        times[5].append(tmp)
    print("FITNESS: {}".format(max(fitness)))
    print(fitness)
    if (args.time):
        print("INIT: {:f}s".format(times[0]))
        print("EVAL: {:f}s".format(sum(times[1]) / gen))
        print("SELE: {:f}s".format(sum(times[2]) / gen))
        print("CROS: {:f}s".format(sum(times[3]) / gen))
        print("MUTA: {:f}s".format(sum(times[4]) / gen))
        print("REPL: {:f}s".format(sum(times[5]) / gen))
    if args.save:
        if len(averages) < 1000:
            averages = averages + ([averages[-1]] * (1000 - len(averages)))
        print("FITNESS: {}".format(averages))


if __name__ == "__main__":
    main()
