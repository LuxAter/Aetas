#include <iostream>

#include "std/std.hpp"
#include "util/util.hpp"

#include "genetic.hpp"

int main(int argc, char* argv[]) {
  aetas::argparse::Parser parser;
  parser.add_option("s|size", "10");
  parser.add_option("m|mutation", "0.1");
  parser.add_option("pm", "0.5");
  aetas::argparse::Arguments args =
      aetas::argparse::parse_args(parser, argc, argv);

  auto eval_func = aetas::sum_eval<int>();

  // Initialization
  std::vector<std::vector<int>> pop;
  for (int i = 0; i < args.geti("size"); ++i) {
    pop.push_back(aetas::random::vrandint(10, 0, 10));
  }

  int counter = 0;

  while (true) {
    // Evaluation
    std::vector<double> fitness;
    for (auto& it : pop) {
      fitness.push_back(std::sum(it));
    }
    std::sort(pop, fitness, true);

    // Termination
    if (fitness.front() >= 90) {
      break;
    }
    // std::cout << fitness.front() << "::" << pop.front() << '\n';
    // int a;
    // std::cin >> a;

    // Selection
    std::vector<double> prob;
    double total_fit = std::sum(fitness);
    for (auto& f : fitness) {
      prob.push_back(f / total_fit);
    }
    std::vector<double> cumulative;
    for (std::size_t i = 0; i < prob.size(); ++i) {
      cumulative.push_back(std::sum(prob, i + 1));
    }

    // std::cout << std::pprint(pop) << '\n';

    // std::cout << fitness << '\n' << prob << '\n' << cumulative << '\n';

    std::vector<std::vector<int>> mating;
    for (int i = 0; i < args.geti("size"); ++i) {
      std::size_t j = 0;
      double r = aetas::random::rand();
      for (j = 0; j < cumulative.size(); ++j) {
        if (cumulative[j] >= r) break;
      }
      mating.push_back(pop[j]);
    }

    // std::cout << std::pprint(mating) << '\n';

    // Recombination
    std::vector<std::vector<int>> new_pop;
    for (int i = 0; i < args.geti("size"); i += 2) {
      std::vector<int> p1 = aetas::random::choice_remove(mating);
      std::vector<int> p2 = aetas::random::choice_remove(mating);
      if (aetas::random::rand() > 0.5) {
        new_pop.push_back(p1);
        new_pop.push_back(p2);
      } else {
        int cross = aetas::random::randint(0, 10);
        std::vector<int> c1, c2;
        for (int j = 0; j < 10; ++j) {
          if (j <= cross) {
            c1.push_back(p2[j]);
            c2.push_back(p1[j]);
          } else {
            c1.push_back(p1[j]);
            c2.push_back(p2[j]);
          }
        }
        new_pop.push_back(c1);
        new_pop.push_back(c2);
      }
    }

    // Mutation
    for (int i = 0; i < new_pop.size(); ++i) {
      if (aetas::random::rand() <= args.getf("mutation")) {
        for (int j = 0; j < 10; ++j) {
          if (aetas::random::rand() <= args.getf("pm")) {
            new_pop[i][j] = aetas::random::randint(0, 10);
          }
        }
      }
    }

    // Replacement
    pop = new_pop;
    counter++;
  }

  std::cout << counter << ":";
  std::cout << pop.front() << '\n';

  return 0;
}
