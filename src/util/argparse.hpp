#ifndef AETAS_ARGPARSE_HPP_
#define AETAS_ARGPARSE_HPP_

#include <map>
#include <string>
#include <vector>

namespace aetas {
namespace argparse {
  struct Arguments {
    std::map<std::string, bool> flg;
    std::map<std::string, std::string> opt;
    std::vector<std::string> args;

    inline double getf(std::string arg) { return std::atof(opt[arg].c_str()); }
    inline int geti(std::string arg) { return std::atoi(opt[arg].c_str()); }
  };
  struct Parser {
    std::string cmd_str, usage_str, version_str;
    std::vector<std::vector<std::string>> names;
    std::map<std::string, std::string> defaults;
    std::map<std::string, std::string> arg_help;
    std::map<std::string, std::string> opt_table;
    std::map<std::string, std::string> flag_table;
    bool help = true;
    bool version = false;

    inline void set_help(bool setting) { help = setting; }
    inline void set_usage(std::string usage) {
      help = true;
      usage_str = usage;
    }
    inline void set_version(std::string ver) {
      version = true;
      version_str = ver;
    }

    void add_flag(std::string name, bool default_val = false,
                  std::string help = "");
    void add_option(std::string name, std::string default_val = "",
                    std::string help = "");
  };

  Arguments parse_args(const Parser& parser, int argc, char* argv[]);
}  // namespace argparse
}  // namespace aetas

#endif  // AETAS_ARGPARSE_HPP_
