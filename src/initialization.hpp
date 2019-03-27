#ifndef AETAS_INITIALIZATION_HPP_
#define AETAS_INITIALIZATION_HPP_

#include <functional>
#include <vector>

#include "util/util.hpp"

namespace aetas {
template <typename _T>
std::vector<_T> rand_initalization() {
  return aetas::random::vrand(10);
}

template <typename _T>
std::function<std::vector<_T>()> rand_init(const std::size_t n,
                                           const _T& minimum,
                                           const _T& maximum) {
  return [n, minimum, maximum]() {
    return aetas::random::vrand(n, minimum, maximum);
  };
}
template <typename _T>
std::function<std::vector<_T>()> randn_init(const std::size_t n,
                                            const _T& minimum,
                                            const _T& maximum) {
  return [n, minimum, maximum]() {
    return aetas::random::vrandn(n, minimum, maximum);
  };
}
template <typename _T>
std::function<std::vector<_T>()> randint_init(const std::size_t n,
                                              const _T& minimum,
                                              const _T& maximum) {
  return [n, minimum, maximum]() {
    return aetas::random::vrandint<_T>(n, minimum, maximum);
  };
}
}  // namespace aetas

#endif  // AETAS_INITIALIZATION_HPP_
