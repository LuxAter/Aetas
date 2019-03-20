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
    flag_table[str] = name;
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
    opt_table[str] = name;
  }
}

iter::argparse::Arguments iter::argparse::parse_args(const Parser& parser,
                                                     int argc, char* argv[]) {
  Arguments args;
  for (auto& it : parser.defaults) {
    if (parser.flag_table.find(it.first) == parser.flag_table.end()) {
      args.flg[it.first] =
          (parser.defaults.at(it.first) == "true" ? true : false);
    } else if (parser.opt_table.find(it.first) == parser.opt_table.end()) {
      args.opt[it.first] = parser.defaults.at(it.first);
    }
  }
  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    while (arg.front() == '-') {
      arg = arg.substr(1);
    }
    typename std::map<std::string, std::string>::const_iterator it =
        parser.flag_table.find(arg);
    if (it != parser.flag_table.end()) {
      args.flg[it->second] =
          (parser.defaults.at(it->second) == "true") ? false : true;
    } else if ((it = parser.opt_table.find(arg)) != parser.opt_table.end()) {
      if (i != argc - 1) {
        args.opt[it->second] = argv[i + 1];
        i++;
      } else {
        printf("\"%s\" requires an argument\n", argv[i]);
      }
    } else {
      args.args.push_back(arg);
    }
  }
  return args;
}
