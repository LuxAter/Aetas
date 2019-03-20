#ifndef AETAS_SUM_HPP_
#define AETAS_SUM_HPP_

#include <algorithm>
#include <numeric>
#include <vector>

namespace std {
template <typename _T>
_T sum(const std::vector<_T>& vec) {
  return std::accumulate(vec.begin(), vec.end(), _T());
}
}  // namespace std

#endif  // AETAS_SUM_HPP_
