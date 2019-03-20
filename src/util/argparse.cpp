#include "argparse.hpp"

#include <map>
#include <string>
#include <vector>

void iter::argparse::Parser::add_flag(std::string name, bool default_val,
                                      std::string help) {
  std::vector<std::string> arg_names;
  while (name.find("|") != std::string::npos) {
    arg_names.push_back(name.substr(0, name.find("|")));
    name = name.substr(name.find("|") + 1);
  }
  arg_names.push_back(name);
  for (auto& str : arg_names) {
    if (str.size() > name.size()) {
      name = str;
    }
  }
  names.push_back(arg_names);
  defaults[name] = (default_val ? "true" : "false");
  arg_help[name] = help;
  for (auto& str : arg_names) {
    name_table[str] = name;
  }
}
void iter::argparse::Parser::add_option(std::string name,
                                        std::string default_val,
                                        std::string help) {
  std::vector<std::string> arg_names;
  while (name.find("|") != std::string::npos) {
    arg_names.push_back(name.substr(0, name.find("|")));
    name = name.substr(name.find("|") + 1);
  }
  arg_names.push_back(name);
  for (auto& str : arg_names) {
    if (str.size() > name.size()) {
      name = str;
    }
  }
  names.push_back(arg_names);
  defaults[name] = default_val;
  arg_help[name] = help;
  for (auto& str : arg_names) {
    name_table[str] = name;
  }
}

iter::argparse::Arguments iter::argparse::parse_args(const Parser& parser,
    int argc, char* argv[]) {

}
