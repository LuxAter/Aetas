#ifndef ITER_PRINT_HPP_
#define ITER_PRINT_HPP_

#include <array>
#include <iostream>
#include <vector>

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

#endif  // ITER_PRINT_HPP_
