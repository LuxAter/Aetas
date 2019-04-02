import numpy as np
import matplotlib.pyplot as plt

def init(n_pop,n_points):
    pop = np.random.rand(n_pop,n_points)
    return pop

def sort_by_fitness(pop, fitness):
    fitness, pop = zip(*sorted(zip(fitness, pop)))
    return pop, fitness


def plot_best(generation, pop, fitness, plot_n=1):
    pop, fitness = sort_by_fitness(pop, fitness)
    for i in range(plot_n):
        X = [pop[i][j] for j in range(0, len(pop[i]), 2)]
        Y = [pop[i][j] for j in range(1, len(pop[i]), 2)]
        plt.plot(X, Y)
    plt.imsave("img/{}.png".format(generation))


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
    pop = initalize(n_pop, n_points)
    for gen in range(100):
        fitness = evaluate(pop)
        print("GEN: {:5} FIT: {}".format(gen, max(fitness)))
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
