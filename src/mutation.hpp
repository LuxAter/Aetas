#ifndef AETAS_MUTATION_HPP_
#define AETAS_MUTATION_HPP_

#include <functional>
#include <vector>

#include "util/util.hpp"

namespace aetas {
template <typename _T>
std::vector<_T> bitwise_mutator(const std::vector<_T>& v) {
  std::vector<_T> vec(v);
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dis{0.0, 1.0};
  for (std::size_t i = 0; i < v.size(); ++i) {
    if (dis(gen) <= 0.2) {
      vec[i] = aetas::random::rand();
    }
  }
  return vec;
}

template <typename _T>
std::function<std::vector<_T>(const std::vector<_T>&)> bitwise_mutr(
    double prob, std::function<_T()> rand_gen = aetas::random::rand()) {
  return [prob, rand_gen](const std::vector<_T>& v) {
    std::vector<_T> vec(v);
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dis{0.0, 1.0};
    for (std::size_t i = 0; i < v.size(); ++i) {
      if (dis(gen) <= 0.2) {
        vec[i] = rand_gen();
      }
    }
    return vec;
  };
}
}  // namespace aetas

#endif  // AETAS_MUTATION_HPP_
