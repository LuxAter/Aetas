#ifndef AETAS_GENETIC_HPP_
#define AETAS_GENETIC_HPP_

#include <array>
#include <functional>
#include <future>
#include <thread>
#include <vector>

#include "evaluation.hpp"
#include "initialization.hpp"
#include "mutation.hpp"
#include "recombination.hpp"
#include "replacement.hpp"
#include "selection.hpp"
#include "termination.hpp"

#include "varia/varia.hpp"

namespace aetas {
template <typename _T = double>
class Genetic {
 public:
  explicit Genetic(varia::Script* script = nullptr)
      : pop_size(100),
        epoch_size(10),
        max_epoch(100),
        initializer(rand_initalization<_T>),
        evaluator(sum_evaluation<_T>),
        selector(roulette_selection<_T>),
        recombinator(two_point_crossover<_T>),
        mutator(bitwise_mutator<_T>),
        replacer(delete_all_replacement<_T>),
        terminator(null_termination),
        script_(script) {
    if (script_ != nullptr) load_script();
  }
  explicit Genetic(std::size_t pop_size, varia::Script* script = nullptr)
      : pop_size(pop_size),
        epoch_size(10),
        max_epoch(100),
        initializer(rand_initalization<_T>),
        evaluator(sum_evaluation<_T>),
        selector(roulette_selection<_T>),
        recombinator(two_point_crossover<_T>),
        mutator(bitwise_mutator<_T>),
        replacer(delete_all_replacement<_T>),
        terminator(null_termination),
        script_(script) {
    if (script_ != nullptr) load_script();
  }

  virtual ~Genetic() {
    if (script_ != nullptr) delete script_;
  }

  void initialize() {
    population_.clear();
    fitness_.clear();
    std::vector<std::future<std::vector<_T>>> threads;
    if (verbose >= 2) {
      std::cout << "INITIALIZTION\n";
    }
    std::cout << pop_size << "\n";
    for (std::size_t i = 0; i < pop_size; ++i) {
      threads.push_back(std::async(initializer));
      if (threads.size() >= thread_count) {
        population_.push_back(threads[0].get());
        threads.erase(threads.begin());
      }
    }
    for (std::size_t i = 0; i < threads.size(); ++i) {
      population_.push_back(threads[i].get());
    }
    threads.clear();
  }
  bool generation() {
    if (verbose >= 2) {
      std::cout << "EVALUATION\n";
    }
    fitness_.clear();
    std::vector<std::future<double>> threads;
    for (std::size_t i = 0; i < pop_size; ++i) {
      threads.push_back(std::async(evaluator, population_[i]));
      if (threads.size() >= thread_count) {
        fitness_.push_back(threads[0].get());
        threads.erase(threads.begin());
      }
    }
    for (std::size_t i = 0; i < threads.size(); ++i) {
      fitness_.push_back(threads[i].get());
    }
    threads.clear();
    std::sort(population_, fitness_, true);

    if (verbose >= 2) {
      std::cout << "TERMINATION\n";
    }
    if (terminator(fitness_.front())) return true;

    if (verbose >= 2) {
      std::cout << "SELECTION\n";
    }
    std::vector<std::vector<_T>> mating_population =
        selector(population_, fitness_);

    if (verbose >= 2) {
      std::cout << "RECOMBINATION\n";
    }
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dis{0.0, 1.0};
    std::vector<std::vector<_T>> new_pop;
    std::vector<std::future<std::array<std::vector<_T>, 2>>> threads_recomb;
    while (mating_population.size() >= 2) {
      std::vector<_T> p1 = aetas::random::choice_remove(mating_population);
      std::vector<_T> p2 = aetas::random::choice_remove(mating_population);
      if (dis(gen) <= crossover_prob) {
        threads_recomb.push_back(std::async(recombinator, p1, p2));
        if (threads_recomb.size() >= thread_count) {
          std::array<std::vector<_T>, 2> children = threads_recomb[0].get();
          new_pop.push_back(children[0]);
          new_pop.push_back(children[1]);
          threads_recomb.erase(threads_recomb.begin());
        }
      } else {
        new_pop.push_back(p1);
        new_pop.push_back(p2);
      }
    }
    for (std::size_t i = 0; i < threads_recomb.size(); ++i) {
      std::array<std::vector<_T>, 2> children = threads_recomb[i].get();
      new_pop.push_back(children[0]);
      new_pop.push_back(children[1]);
    }
    threads_recomb.clear();

    if (verbose >= 2) {
      std::cout << "MUTATION\n";
    }
    std::vector<std::pair<std::size_t, std::future<std::vector<_T>>>>
        threads_mutate;
    for (std::size_t i = 0; i < new_pop.size(); ++i) {
      if (dis(gen) <= mutation_prob) {
        threads_mutate.push_back(
            std::make_pair(i, std::async(mutator, new_pop[i])));
        if (threads_mutate.size() >= thread_count) {
          new_pop[threads_mutate[0].first] = threads_mutate[0].second.get();
          threads_mutate.erase(threads_mutate.begin());
        }
      }
    }
    for (std::size_t i = 0; i < threads_mutate.size(); ++i) {
      new_pop[threads_mutate[i].first] = threads_mutate[i].second.get();
    }
    threads_mutate.clear();

    if (verbose >= 2) {
      std::cout << "REPLACEMENT\n";
    }
    population_ = replacer(new_pop, population_, fitness_);
    generations++;
    return false;
  }
  bool epoch() {
    for (std::size_t i = 0; i < epoch_size; ++i) {
      if (generation()) return true;
    }
    epochs++;
    if (verbose != 0) {
      std::cout << epochs << ":" << generations << "  " << fitness_.front()
                << "\n";

      for (std::size_t i = 0; i < top_pop; ++i) {
        std::cout << fitness_[i] << "  " << population_[i] << '\n';
      }
    }
    return false;
  }
  void terminate() {
    population_.clear();
    fitness_.clear();
    generations = 0;
    epochs = 0;
  }

  bool exec() {
    initialize();
    for (std::size_t i = 0; i < max_epoch; ++i) {
      if (epoch()) return true;
    }
    return false;
  }

  double get_best_fitness() const { return fitness_.front(); }
  std::vector<_T> get_best() const { return population_.front(); }

  std::size_t pop_size, epoch_size, max_epoch, thread_count = 4;
  std::size_t epochs = 0, generations = 0;
  std::size_t top_pop = 5;
  uint8_t verbose = 1;

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
  void load_script() {
    if (script_->hasi("pop_size")) pop_size = script_->geti("pop_size");
    if (script_->hasi("epoch_size")) epoch_size = script_->geti("epoch_size");
    if (script_->hasi("max_epoch")) max_epoch = script_->geti("max_epoch");
    if (script_->has("initializer")) {
      if (script_->hass("initializer")) {
      } else if (script_->hasf("initializer")) {
        initializer = script_->func<std::vector<_T>>("initializer");
      }
    }
    if (script_->has("evaluator")) {
      if (script_->hass("evaluator")) {
      } else if (script_->hasf("evaluator")) {
        evaluator = script_->func<double, std::vector<_T>>("evaluator");
      }
    }
    if (script_->has("selector")) {
      if (script_->hass("selector")) {
      } else if (script_->hasf("selector")) {
        // XXX
      }
    }
    if (script_->has("recombinator")) {
      if (script_->hass("recombinator")) {
      } else if (script_->hasf("recombinator")) {
        // XXX
      }
    }
    if (script_->has("mutator")) {
      if (script_->hass("mutator")) {
      } else if (script_->hasf("mutator")) {
        mutator = script_->func<std::vector<_T>, std::vector<_T>>("mutator");
      }
    }
    if (script_->has("replacer")) {
      if (script_->hass("replacer")) {
      } else if (script_->hasf("replacer")) {
        // XXX
      }
    }
    if (script_->has("terminator")) {
      if (script_->hass("terminator")) {
      } else if (script_->hasf("terminator")) {
          std::cout << "A\n";
        terminator = script_->func<int, double>("terminator");
      }
    }
  }

  std::vector<std::vector<_T>> population_;
  std::vector<double> fitness_;
  varia::Script* script_;
};
}  // namespace aetas

#endif  // AETAS_GENETIC_HPP_
