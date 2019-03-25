#include <iostream>

#include "script/script.hpp"
#include "std/std.hpp"
#include "util/util.hpp"

int main(int argc, char* argv[]) {
  // Argument Parser
  // aetas::argparse::Parser parser;
  // parser.add_option("s|size", "10");
  // aetas::argparse::Arguments args =
  //     aetas::argparse::parse_args(parser, argc, argv);
  //
  // // Initial Population
  // std::vector<std::vector<int>> pop;
  // for (int i = 0; i < args.geti("size"); ++i) {
  //   pop.push_back(aetas::random::randint(10, 0, 11));
  // }
  //
  // // Calculate Initial Fitness
  // std::vector<int> fitness;
  // for (auto& it : pop) {
  //   fitness.push_back(std::sum(it));
  // }
  //
  // std::cout << fitness << "\n";
  // std::cout << std::max(fitness) << "\n";
  // std::cout << std::min(fitness) << "\n";
  // std::cout << std::range(fitness) << "\n";
  // std::cout << std::mean(fitness) << "\n";

  // aetas::script::Script src = aetas::script::open("resources/test.lua");
  aetas::script::Script src =
      std::reinterpret_pointer_cast<aetas::script::ScriptCore>(
          std::make_shared<aetas::script::Lua>("resources/test.lua"));
  // std::shared_ptr<aetas::script::Lua> src =
  // std::make_shared<aetas::script::Lua>("resources/test.lua");
  auto vals = src->call<double>("rand");
  // auto vals = src.call<double>("rand");
  std::cout << vals << "\n";
  // std::vector<double> vec = src.initialization<double>();
  // std::cout << vec << "\n";
  // std::cout << src.evaluation(vec);
  // std::cout << ":" << std::sum(vec) << "\n";

  return 0;
}
