/**
 * @file vector.hpp
 * @brief Additional vector based functions.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2019-03-20
 */

#ifndef AETAS_VECTOR_HPP_
#define AETAS_VECTOR_HPP_

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace std {

template <typename>
struct is_vector : std::false_type {};

template <typename _T, typename _A>
struct is_vector<std::vector<_T, _A>> : std::true_type {};

/**
 * @brief Finds the sum of the values in a vector.
 *
 * @tparam _T Type of vector.
 * @param vec Vector to accumulate.
 *
 * @return Sum of the values in vec.
 */
template <typename _T>
_T sum(const std::vector<_T>& vec) {
  return std::accumulate(vec.begin(), vec.end(), _T());
}

/**
 * @brief Finds the sum of the values in a vector.
 *
 * @tparam _T Type of vector.
 * @param vec Vector to accumulate.
 *
 * @return Sum of the values in vec.
 */
template <typename _T>
_T sum(const std::vector<_T>& vec, const std::size_t& i) {
  return std::accumulate(vec.begin(), vec.begin() + i, _T());
}

/**
 * @brief Finds the mean of the values in a vector.
 *
 * @tparam _T Type of vector.
 * @param vec Vector to find the mean of.
 *
 * @return Mean value of the values stored in vec.
 */
template <typename _T>
_T mean(const std::vector<_T>& vec) {
  return std::accumulate(vec.begin(), vec.end(), _T()) / vec.size();
}

/**
 * @brief Finds maximum value in a vector.
 *
 * @tparam _T Type of vector.
 * @param vec Vector to find maximum of.
 *
 * @return Maximum value stored in vec.
 */
template <typename _T>
_T max(const std::vector<_T>& vec) {
  return *std::max_element(vec.begin(), vec.end());
}

/**
 * @brief Finds minimum value in a vector.
 *
 * @tparam _T Type of vector.
 * @param vec Vector to find minimum of.
 *
 * @return Minimum value stored in vec.
 */
template <typename _T>
_T min(const std::vector<_T>& vec) {
  return *std::min_element(vec.begin(), vec.end());
}

/**
 * @brief Finds range of values in vector.
 *
 * This is equivalent to
 * ```
 * std::max(vec) - std::min(vec)
 * ```
 *
 * @tparam _T Type of vector.
 * @param vec Vector to find range of.
 *
 * @return Range of the values sotred in vec.
 */
template <typename _T>
_T range(const std::vector<_T>& vec) {
  std::pair<typename std::vector<_T>::const_iterator,
            typename std::vector<_T>::const_iterator>
      vals = std::minmax_element(vec.begin(), vec.end());
  return (*(vals.second) - *(vals.first));
}

template <typename _T>
std::vector<_T> sort(const std::vector<_T>& lhs, bool reverse_vec = false) {
  std::vector<_T> ret(lhs);
  std::sort(ret.begin(), ret.end());
  if (reverse_vec) {
    std::reverse(ret.begin(), ret.end());
  }
  return ret;
}

/**
 * @brief Sorts one vector by the values of a second vector.
 *
 * @tparam _T Type of vector to sort.
 * @tparam _U Type of vector to sort by.
 * @param lhs Vector to sort.
 * @param rhs Vector to use as sorting keys.
 *
 * @return Sorted version of ``lhs`` and ``rhs``.
 */
template <typename _T, typename _U>
void sort(std::vector<_T>& lhs, std::vector<_U>& rhs,
          bool reverse_vec = false) {
  std::vector<std::pair<_U, _T>> vec;
  for (std::size_t i = 0; i < lhs.size() && i < rhs.size(); ++i) {
    vec.push_back({rhs[i], lhs[i]});
  }
  std::sort(vec.begin(), vec.end());
  lhs.clear();
  rhs.clear();
  for (std::size_t i = 0; i < vec.size(); ++i) {
    lhs.push_back(vec[i].second);
    rhs.push_back(vec[i].first);
  }
  if (reverse_vec) {
    std::reverse(lhs.begin(), lhs.end());
    std::reverse(rhs.begin(), rhs.end());
  }
}

/**
 * @brief Stream operator for Vector classes.
 *
 * This is just an overload to allow for printing of vectors.
 *
 * @tparam _T Type of vector.
 * @param out Output stream.
 * @param rhs Vector to print to stream.
 *
 * @return Output stream.
 */
template <typename _T>
std::ostream& operator<<(std::ostream& out, const std::vector<_T>& rhs) {
  out << "<";
  for (std::size_t i = 0; i < rhs.size(); ++i) {
    out << rhs[i];
    if (i != rhs.size() - 1) {
      out << ", ";
    }
  }
  out << ">";
  return out;
}

template <typename _T>
std::string pprint(const std::vector<_T>& rhs) {
  std::stringstream ss;
  ss << "<\n  ";
  for (std::size_t i = 0; i < rhs.size(); ++i) {
    ss << rhs[i];
    if (i != rhs.size() - 1) {
      ss << "\n  ";
    }
  }
  ss << "\n>";
  return ss.str();
}

}  // namespace std

#endif  // AETAS_VECTOR_HPP_
