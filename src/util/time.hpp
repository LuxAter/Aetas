/**
 * @file time.hpp
 * @brief Wrappers for standard time utilities.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2019-03-20
 */

#ifndef AETAS_TIME_HPP_
#define AETAS_TIME_HPP_

#include <chrono>

namespace aetas {
namespace time {
  /**
   * @brief Defines clock type for higher precision.
   */
  typedef std::chrono::time_point<std::chrono::system_clock> time_t;
  /**
   * @brief Gets the current clock time.
   *
   * @return Clock time point.
   */
  std::chrono::time_point<std::chrono::system_clock> now();
  /**
   * @brief Starts a timer
   *
   * This is the same as `aetas:time::now()`.
   *
   * @return Clock time point of start time.
   */
  std::chrono::time_point<std::chrono::system_clock> start();
  /**
   * @brief Ends a timer and finds the duration in seconds.
   *
   * This finds the difference between the current time and the start time
   * passed, and converts that duration into seconds as a double.
   *
   * @param start Start time of the timer.
   *
   * @return Ellapsed time as a ``double`` with units of seconds.
   */
  double stop(const std::chrono::time_point<std::chrono::system_clock>& start);
}  // namespace time
}  // namespace aetas

#endif  // AETAS_TIME_HPP_
