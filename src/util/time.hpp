#ifndef AETAS_TIME_HPP_
#define AETAS_TIME_HPP_

#include <chrono>

namespace aetas {
namespace time {
  typedef std::chrono::time_point<std::chrono::system_clock> time_t;
  std::chrono::time_point<std::chrono::system_clock> now();
  std::chrono::time_point<std::chrono::system_clock> start();
  double stop(const std::chrono::time_point<std::chrono::system_clock>& start);
}  // namespace time
}  // namespace aetas

#endif  // AETAS_TIME_HPP_
