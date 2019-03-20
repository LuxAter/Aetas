/**
 * @file range.hpp
 * @brief Implements python-like range functions.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2019-03-20
 */

#ifndef AETAS_RANGE_HPP_
#define AETAS_RANGE_HPP_

#include <vector>

namespace aetas {
namespace range {
  /**
   * @brief Constructs range of values.
   *
   * @tparam _T Type of vector to construct.
   * @param stop The maximum value to goto.
   *
   * @return Vector containing monotonically increasing values of type ``_T`` in
   * the range \f$[0,stop)\f$.
   */
  template <typename _T>
  std::vector<_T> range(_T stop) {
    std::vector<_T> out;
    for (_T i = _T(); i < stop; ++i) {
      out.push_back(i);
    }
    return out;
  }

  /**
   * @brief Constructs range of values.
   *
   * @tparam _T Type of vector to construct.
   * @param start Starting value.
   * @param stop Maximum value to goto.
   *
   * @return Vector containing monotonically increasing values of type ``_T`` in
   * the range \f$[start,stop)\f$.
   */
  template <typename _T>
  std::vector<_T> range(_T start, _T stop) {
    std::vector<_T> out;
    for (_T i = start; i < stop; ++i) {
      out.push_back(i);
    }
    return out;
  }

  /**
   * @brief Constructs range of values.
   *
   * @tparam _T Type of vector to construct.
   * @param start Starting value.
   * @param stop Maximum value to goto.
   * @param step Step size of the increment.
   *
   * @return Vector containing increasing values of type ``_T`` in the range
   * \f$[start,stop)\f$ increasing by $step$ each time.
   */
  template <typename _T>
  std::vector<_T> range(_T start, _T stop, _T step) {
    std::vector<_T> out;
    for (_T i = start; i < stop; i += step) {
      out.push_back(i);
    }
    return out;
  }

  /**
   * @brief Constructs range of values.
   *
   * @tparam _T Type of vector to construct.
   * @param start Starting value.
   * @param stop Maximum value to goto.
   * @param n Number of steps to make between the values.
   *
   * @return Vector containing increasing values of type ``_T`` in the range
   * \f$[start,stop)\f$, with ``n`` values in the vector, or ``n`` steps in the
   * range.
   */
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
}  // namespace aetas

#endif  // AETAS_RANGE_HPP_
