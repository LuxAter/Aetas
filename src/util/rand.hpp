#ifndef AETAS_RAND_HPP_
#define AETAS_RAND_HPP_

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <vector>

namespace aetas {
namespace random {
  double rand(double low = 0.0, double high = 1.0);
  std::vector<double> rand(const unsigned& n, double low = 0.0,
                           double high = 1.0);
  double randn(double mean = 0.0, double variance = 1.0);
  std::vector<double> randn(const unsigned& n, double mean = 0.0,
                            double variance = 1.0);
  int randint(int low = 0, int high = std::numeric_limits<int>::max());
  std::vector<int> randint(const unsigned& n, int low = 0,
                           int high = std::numeric_limits<int>::max());

  template <typename _T>
  _T choice(const std::vector<_T>& a) {
    std::vector<_T> out;
    std::sample(a.begin(), a.end(), std::back_inserter(out), 1,
                std::mt19937{std::random_device{}()});
    return out.first();
  }

  template <typename _T>
  std::vector<_T> choice(const std::vector<_T>& a, const unsigned& n) {
    std::vector<_T> out;
    std::sample(a.begin(), a.end(), std::back_inserter(out), n,
                std::mt19937{std::random_device{}()});
    return out;
  }

  template <typename _T>
  std::vector<_T> shuffle(const std::vector<_T>& a) {
    std::vector<_T> out(a);
    std::shuffle(out.begin(), out.end(), std::mt19937{std::random_device{}()});
    return out;
  }
}  // namespace random
}  // namespace aetas

#endif  // AETAS_RAND_HPP_
