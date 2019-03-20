#ifndef ITER_RANGE_HPP_
#define ITER_RANGE_HPP_

#include <vector>

namespace iter {
namespace range {
  template <typename _T>
  std::vector<_T> range(_T stop) {
    std::vector<_T> out;
    for (_T i = _T(); i < stop; ++i) {
      out.push_back(i);
    }
    return out;
  }

  template <typename _T>
  std::vector<_T> range(_T start, _T stop) {
    std::vector<_T> out;
    for (_T i = start; i < stop; ++i) {
      out.push_back(i);
    }
    return out;
  }

  template <typename _T>
  std::vector<_T> range(_T start, _T stop, _T step) {
    std::vector<_T> out;
    for (_T i = start; i < stop; i += step) {
      out.push_back(i);
    }
    return out;
  }

  template <typename _T>
  std::vector<_T> linspace(_T start, _T stop, unsigned n = 50) {
    std::vector<_T> out;
    _T step = (stop - start) / static_cast<_T>(n);
    for (_T i = start; i < stop; i += step) {
      out.push_back(i);
    }
    return out;
  }
}  // namespace range
}  // namespace iter

#endif  // ITER_RANGE_HPP_
