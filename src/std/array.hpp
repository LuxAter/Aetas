#ifndef AETAS_ARRAY_HPP_
#define AETAS_ARRAY_HPP_

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

namespace std {

template <typename _T, std::size_t _N>
_T sum(const std::array<_T, _N>& vec) {
  return std::accumulate(vec.begin(), vec.end(), _T());
}
template <typename _T, std::size_t _N>
_T mean(const std::array<_T, _N>& vec) {
  return std::accumulate(vec.begin(), vec.end(), _T()) / vec.size();
}
template <typename _T, std::size_t _N>
_T max(const std::array<_T, _N>& vec) {
  return *std::max_element(vec.begin(), vec.end());
}
template <typename _T, std::size_t _N>
_T min(const std::array<_T, _N>& vec) {
  return *std::min_element(vec.begin(), vec.end());
}
template <typename _T, std::size_t _N>
_T range(const std::array<_T, _N>& vec) {
  std::pair<typename std::array<_T, _N>::const_iterator,
            typename std::array<_T, _N>::const_iterator>
      vals = std::minmax_element(vec.begin(), vec.end());
  return (*(vals.second) - *(vals.first));
}
template <typename _T, std::size_t _N>
std::ostream& operator<<(std::ostream& out, const std::array<_T, _N>& rhs) {
  out << "[";
  for (std::size_t i = 0; i < rhs.size(); ++i) {
    out << rhs[i];
    if (i != rhs.size() - 1) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}
}  // namespace std

#endif  // AETAS_ARRAY_HPP_
