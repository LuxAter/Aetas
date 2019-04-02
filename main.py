#hello everyone
def main():
    n_pop = 100
    n_points = 10
    n_keep = 10
    prob_m = 0.2
    pop = initalize(n_pop, n_points)
    for gen in range(100):
        fitness = evaluate(pop)
        if terminate(fitness):
            break
        new_pop = selection(pop, fitness, n_keep)
        new_pop = crossover(new_pop, k)
        new_pop = mutate(new_pop, prob_m)
        pop = replace(pop, fitness, new_pop, n_keep)
    print(max(fitness))
