/**
 * @file rand.hpp
 * @brief Random value generation.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2019-03-20
 */

#ifndef AETAS_RAND_HPP_
#define AETAS_RAND_HPP_

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <vector>

namespace aetas {
namespace random {
  /**
   * @brief Generates uniform random value.
   *
   * @param low Lower bound of uniform distribution.
   * @param high Upper bound of uniform distribution.
   *
   * @return Random value in the range \f$[low,high)\f$.
   */
  double rand(double low = 0.0, double high = 1.0);
  /**
   * @brief Generates a vector of uniform random values.
   *
   * @param n Number of values to generate
   * @param low Lower bound of uniform distribution.
   * @param high Upper bound of uniform distribution.
   *
   * @return Vector of ``n`` random values in the range \f$[low,high)\f$.
   */
  std::vector<double> vrand(const unsigned& n, double low = 0.0,
                           double high = 1.0);
  /**
   * @brief Generates normal random value.
   *
   * @param mean Mean of the normal distribution.
   * @param variance Variance of the uniform distribution.
   *
   * @return Random value from a normal distribution with mean of ``mean`` and
   * variance of ``variance``.
   */
  double randn(double mean = 0.0, double variance = 1.0);
  /**
   * @brief Generates a vector normal random value.
   *
   * @param n Number of values to generate.
   * @param mean Mean of the normal distribution.
   * @param variance Variance of the uniform distribution.
   *
   * @return Vector of ``n`` random values from a normal distribution with mean
   * of ``mean`` and variance of ``variance``.
   */
  std::vector<double> vrandn(const unsigned& n, double mean = 0.0,
                            double variance = 1.0);
  /**
   * @brief Generates a uniform random integer.
   *
   * @param low Lower bond on the uniform distribution.
   * @param high Upper bound on the uniform distribution.
   *
   * @return Random integer in range \f$[low,high)\f$.
   */
  template <typename _T=int>
    _T randint(_T low = 0, _T high = std::numeric_limits<int>::max()){
    std::mt19937 gen(std::random_device{}());
    return std::uniform_int_distribution<_T>{low, high}(gen);
    }
  /**
   * @brief Generates a vector of uniform random integers.
   *
   * @param n Number of values to generate.
   * @param low Lower bond on the uniform distribution.
   * @param high Upper bound on the uniform distribution.
   *
   * @return Vector of ``n`` random integers in range \f$[low,high)\f$.
   */
  template <typename _T=int>
  std::vector<_T> vrandint(const unsigned& n, _T low = 0,
                          _T high = std::numeric_limits<_T>::max()) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<_T> dis{low, high};
    std::vector<_T> vals;
    for (unsigned i = 0; i < n; ++i) {
      vals.push_back(dis(gen));
    }
    return vals;
  }

  /**
   * @brief Picks a random value from a vector.
   *
   * @tparam _T Type of vector.
   * @param a Vector to pick value from.
   *
   * @return A random element of the vector ``a``.
   */
  template <typename _T>
  _T choice(const std::vector<_T>& a) {
    std::vector<_T> out;
    std::sample(a.begin(), a.end(), std::back_inserter(out), 1,
                std::mt19937{std::random_device{}()});
    return out.first();
  }

  /**
   * @brief Picks random values from a vector.
   *
   * @tparam _T Type of vector.
   * @param a Vector to pick values from.
   * @param n Number of values to pick.
   *
   * @return A vector of ``n`` elements picked randomly from the vector ``a``.
   */
  template <typename _T>
  std::vector<_T> choice(const std::vector<_T>& a, const unsigned& n) {
    std::vector<_T> out;
    std::sample(a.begin(), a.end(), std::back_inserter(out), n,
                std::mt19937{std::random_device{}()});
    return out;
  }

  /**
   * @brief Picks a random value from a vector, and removes it.
   *
   * @tparam _T Type of vector.
   * @param a Vector to pick value from.
   *
   * @return A random element of the vector ``a``.
   */
  template <typename _T>
  _T choice_remove(std::vector<_T>& a) {
    std::mt19937 gen(std::random_device{}());
    std::size_t i =
        std::uniform_int_distribution<std::size_t>{0, a.size() - 1}(gen);
    _T val = a[i];
    a.erase(a.begin() + i);
    return val;
  }

  /**
   * @brief Shuffles a vector to a random order.
   *
   * @tparam _T Type of vector.
   * @param a Vector to shuffle.
   *
   * @return Vector containing the exact elements from ``a``, but reordered
   * randomly.
   */
  template <typename _T>
  std::vector<_T> shuffle(const std::vector<_T>& a) {
    std::vector<_T> out(a);
    std::shuffle(out.begin(), out.end(), std::mt19937{std::random_device{}()});
    return out;
  }
}  // namespace random
}  // namespace aetas

#endif  // AETAS_RAND_HPP_
