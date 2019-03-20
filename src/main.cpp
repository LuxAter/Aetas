#include <iostream>

#include "std/std.hpp"
#include "util/util.hpp"

int main(int argc, char* argv[]) {
  // Argument Parser
  aetas::argparse::Parser parser;
  parser.add_option("s|size", "10");
  aetas::argparse::Arguments args =
      aetas::argparse::parse_args(parser, argc, argv);

  // Initial Population
  std::vector<std::vector<int>> pop;
  for (int i = 0; i < args.geti("size"); ++i) {
    pop.push_back(aetas::random::randint(10, 0, 10));
  }

  // Calculate Initial Fitness
  std::vector<int> fitness;
  for (auto& it : pop) {
    fitness.push_back(std::sum(it));
  }

  return 0;
}
