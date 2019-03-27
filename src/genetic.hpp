#ifndef AETAS_GENETIC_HPP_
#define AETAS_GENETIC_HPP_

#include <array>
#include <functional>
#include <vector>

#include "evaluation.hpp"
#include "initialization.hpp"
#include "mutation.hpp"
#include "recombination.hpp"
#include "replacement.hpp"
#include "selection.hpp"
#include "termination.hpp"

namespace aetas {
template <typename _T = double>
class Genetic {
 public:
  Genetic()
      : pop_size(100),
        epoch_size(10),
        max_epoch(100),
        initializer(rand_initalization),
        evaluator(sum_evaluation),
        selector(roulette_selection),
        recombinator(two_point_crossover),
        mutator(bitwise_mutator),
        replacer(delete_all_replacement),
        terminator(null_termination) {}
  explicit Genetic(std::size_t pop_size)
      : pop_size(pop_size),
        epoch_size(10),
        max_epoch(100),
        initializer(rand_initalization),
        evaluator(sum_eval),
        recombinator(two_point_crossover),
        mutator(bitwise_mutator),
        replacer(delete_all_replacement),
        terminator(null_termination) {}

  void initalize() {
    population_.clear();
    fitness_.clear();
    for (std::size_t i = 0; i < pop_size; ++i) {
      // initalizer
    }
  }
  bool generation() {
    for (std::size_t i = 0; i < pop_size; ++i) {
      // evaluator
    }
    std::sort(population_, fitness_, true);

    if (terminator(fitness_.front())) return true;

    std::vector<std::vector<_T>> mating_population =
        selector(population_, fitness_);

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dis{0.0, 1.0};
    std::vector<std::vector<_T>> new_pop;
    while (mating_population.size() >= 2) {
      std::vector<_T> p1 = aetas::random::choice_remove(mating_population);
      std::vector<_T> p2 = aetas::random::choice_remove(mating_population);
      if (dis(gen) <= crossover_prob) {
        // recombinator
      } else {
        new_pop.push_back(p1);
        new_pop.push_back(p2);
      }
    }

    for (std::size_t i = 0; i < new_pop.size(); ++i) {
      if (dis(gen) <= mutation_prob) {
        // mutator
      }
    }

    population_ = replacer(new_pop, population_, fitness_);
    return false;
  }
  bool epoch() {
    for (std::size_t i = 0; i < epoch_size; ++i) {
      if (generation()) return true;
    }
    return false;
  }
  void terminate() {
    population_.clear();
    fitness_.clear();
  }

  bool exec() {
    initalize();
    for (std::size_t i = 0; i < max_epoch; ++i) {
      if (epoch()) return true;
    }
    return false;
  }

  std::size_t pop_size, epoch_size, max_epoch;

  double crossover_prob = 0.5, mutation_prob = 0.2;

  std::function<std::vector<_T>()> initializer;
  std::function<double(const std::vector<_T>&)> evaluator;
  std::function<std::vector<std::vector<_T>>(
      const std::vector<std::vector<_T>>&, const std::vector<double>&)>
      selector;
  std::function<std::array<std::vector<_T>, 2>(const std::vector<_T>&,
                                               const std::vector<_T>&)>
      recombinator;
  std::function<std::vector<_T>(const std::vector<_T>&)> mutator;
  std::function<std::vector<std::vector<_T>>(
      const std::vector<std::vector<_T>>&, const std::vector<std::vector<_T>>&,
      const std::vector<double>&)>
      replacer;
  std::function<bool(const double&)> terminator;

 private:
  std::vector<std::vector<_T>> population_;
  std::vector<double> fitness_;
};
}  // namespace aetas

#endif  // AETAS_GENETIC_HPP_
