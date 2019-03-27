#ifndef AETAS_EVAULATION_HPP_
#define AETAS_EVAULATION_HPP_

#include <functional>
#include <vector>

#include "std/std.hpp"

namespace aetas {
template <typename _T>
double sum_evaluation(const std::vector<_T>& v) {
  return static_cast<double>(std::sum(v));
}
template <typename _T>
double invsum_evaluation(const std::vector<_T>& v) {
  return 1.0 / static_cast<double>(std::sum(v));
}

template <typename _T>
std::function<double(const std::vector<_T>&)> sum_eval() {
  return
      [](const std::vector<_T>& v) { return static_cast<double>(std::sum(v)); };
}
template <typename _T>
std::function<double(const std::vector<_T>&)> invsum_eval() {
  return [](const std::vector<_T>& v) {
    return 1.0 / static_cast<double>(std::sum(v));
  };
}
}  // namespace aetas

#endif  // AETAS_EVAULATION_HPP_
