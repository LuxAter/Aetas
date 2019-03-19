#include "time.hpp"

#include <chrono>

std::chrono::time_point<std::chrono::system_clock> iter::time::now()
{
  return std::chrono::system_clock::now();
}

std::chrono::time_point<std::chrono::system_clock> iter::time::start()
{
  return std::chrono::system_clock::now();
}
double iter::time::stop(const std::chrono::time_point<std::chrono::system_clock>& start)
{
  return std::chrono::duration<double>(std::chrono::system_clock::now() - start).count();
}
