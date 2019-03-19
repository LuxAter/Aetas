#include "util/time.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  iter::time::time_t timer = iter::time::start();
  double diff = iter::time::stop(timer);
  std::cout << diff << "\n";
  return 0;
}
