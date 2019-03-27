#ifndef AETAS_RECOMBINATION_HPP_
#define AETAS_RECOMBINATION_HPP_

#include <array>
#include <functional>
#include <vector>

#include "std/std.hpp"
#include "util/util.hpp"

namespace aetas {
template <typename _T>
std::array<std::vector<_T>, 2> one_point_crossover(const std::vector<_T>& p1,
                                                   const std::vector<_T>& p2) {
  std::size_t chromo_size = std::min(p1.size(), p2.size());
  std::size_t cross = aetas::random::randint<std::size_t>(0, chromo_size);
  std::array<std::vector<_T>, 2> children;
  for (std::size_t i = 0; i < chromo_size; ++i) {
    if (i <= cross) {
      children[0].push_back(p2[i]);
      children[1].push_back(p1[i]);
    } else {
      children[0].push_back(p1[i]);
      children[1].push_back(p2[i]);
    }
  }
  return children;
}

template <typename _T>
std::array<std::vector<_T>, 2> two_point_crossover(const std::vector<_T>& p1,
                                                   const std::vector<_T>& p2) {
  std::size_t chromo_size = std::min(p1.size(), p2.size());
  std::vector<std::size_t> cross =
      std::sort(aetas::random::vrandint<std::size_t>(2, 0, chromo_size));
  std::array<std::vector<_T>, 2> children;
  std::size_t index = 0;
  for (std::size_t i = 0; i < chromo_size; ++i) {
    if (i > cross[index]) {
      index++;
    }
    if (index % 2 == 0) {
      children[0].push_back(p2[i]);
      children[1].push_back(p1[i]);
    } else {
      children[0].push_back(p1[i]);
      children[1].push_back(p2[i]);
    }
  }
  return children;
}

template <typename _T>
std::function<std::array<std::vector<_T>, 2>(const std::vector<_T>&,
                                             const std::vector<_T>&)>
k_point_cross(const std::size_t k) {
  return [k](const std::vector<_T>& p1, const std::vector<_T>& p2) {
    std::size_t chromo_size = std::min(p1.size(), p2.size());
    std::vector<std::size_t> cross =
        std::sort(aetas::random::vrandint<std::size_t>(k, 0, chromo_size));
    std::array<std::vector<_T>, 2> children;
    std::size_t index = 0;
    for (std::size_t i = 0; i < chromo_size; ++i) {
      if (i > cross[index]) {
        index++;
      }
      if (index % 2 == 0) {
        children[0].push_back(p2[i]);
        children[1].push_back(p1[i]);
      } else {
        children[0].push_back(p1[i]);
        children[1].push_back(p2[i]);
      }
    }
    return children;
  };
}
}  // namespace aetas

#endif  // AETAS_RECOMBINATION_HPP_
