#ifndef AETAS_SELECTION_HPP_
#define AETAS_SELECTION_HPP_

#include <functional>
#include <vector>

#include "std/std.hpp"
#include "util/util.hpp"

namespace aetas {
template <typename _T>
std::vector<std::vector<_T>> roulette_selection(
    const std::vector<std::vector<_T>>& population,
    const std::vector<double>& fitness) {
  std::vector<double> probability;
  double total_fitness = std::sum(fitness);
  double cumulative_prob = 0.0;
  for (std::size_t i = 0; i < fitness.size(); ++i) {
    cumulative_prob += (fitness[i] / total_fitness);
    probability.push_back(cumulative_prob);
  }
  std::vector<std::vector<_T>> mating_population;
  for (int i = 0; i < population.size(); ++i) {
    std::size_t j = 0;
    double r = aetas::random::rand();
    for (j = 0; j < probability.size(); ++j) {
      if (probability[j] >= r) break;
    }
    mating_population.push_back(population[j]);
  }
  return mating_population;
}

template <typename _T>
std::function<std::vector<std::vector<_T>>(const std::vector<std::vector<_T>>&,
                                           const std::vector<double>&)>
roulette_selc(std::size_t n) {
  return [n](const std::vector<std::vector<_T>>& population,
             const std::vector<double>& fitness) {
    std::vector<double> probability;
    double total_fitness = std::sum(fitness);
    double cumulative_prob = 0.0;
    for (std::size_t i = 0; i < fitness.size(); ++i) {
      cumulative_prob += (fitness[i] / total_fitness);
      probability.push_back(cumulative_prob);
    }
    std::vector<std::vector<_T>> mating_population;
    for (int i = 0; i < n; ++i) {
      std::size_t j = 0;
      double r = aetas::random::rand();
      for (j = 0; j < probability.size(); ++j) {
        if (probability[j] >= r) break;
      }
      mating_population.push_back(population[j]);
    }
    return mating_population;
  };
}
}  // namespace aetas

#endif  // AETAS_SELECTION_HPP_
