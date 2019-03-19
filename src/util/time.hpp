#ifndef ITER_TIME_HPP_
#define ITER_TIME_HPP_

#include <chrono>

namespace iter {
namespace time {
  typedef std::chrono::time_point<std::chrono::system_clock> time_t;
  std::chrono::time_point<std::chrono::system_clock> now();
  std::chrono::time_point<std::chrono::system_clock> start();
  double stop(const std::chrono::time_point<std::chrono::system_clock>& start);
} // namespace time
} // namespace iter

#endif // ITER_TIME_HPP_
