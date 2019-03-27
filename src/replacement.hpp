#ifndef AETAS_REPLACEMENT_HPP_
#define AETAS_REPLACEMENT_HPP_

#include <functional>
#include <vector>

namespace aetas {
template <typename _T>
std::vector<std::vector<_T>> delete_all_replacement(
    const std::vector<std::vector<_T>>& new_pop,
    const std::vector<std::vector<_T>>& old_pop,
    const std::vector<double>& fitness) {
  return new_pop;
}
}  // namespace aetas

#endif  // AETAS_REPLACEMENT_HPP_
