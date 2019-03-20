#include "rand.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <vector>

double aetas::random::rand(double low, double high) {
  std::mt19937 gen(std::random_device{}());
  return std::uniform_real_distribution<double>{low, high}(gen);
}
std::vector<double> aetas::random::rand(const unsigned& n, double low,
                                        double high) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dis{low, high};
  std::vector<double> vals;
  for (unsigned i = 0; i < n; ++i) {
    vals.push_back(dis(gen));
  }
  return vals;
}
double aetas::random::randn(double mean, double variance) {
  std::mt19937 gen(std::random_device{}());
  return std::normal_distribution<double>{mean, std::sqrt(variance)}(gen);
}
std::vector<double> aetas::random::randn(const unsigned& n, double mean,
                                         double variance) {
  std::mt19937 gen(std::random_device{}());
  std::normal_distribution<double> dis{mean, std::sqrt(variance)};
  std::vector<double> vals;
  for (unsigned i = 0; i < n; ++i) {
    vals.push_back(dis(gen));
  }
  return vals;
}
int aetas::random::randint(int low, int high) {
  std::mt19937 gen(std::random_device{}());
  return std::uniform_int_distribution<int>{low, high}(gen);
}
std::vector<int> aetas::random::randint(const unsigned& n, int low, int high) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dis{low, high};
  std::vector<int> vals;
  for (unsigned i = 0; i < n; ++i) {
    vals.push_back(dis(gen));
  }
  return vals;
}
