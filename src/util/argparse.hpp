/**
 * @file argparse.hpp
 * @brief Command line argument parser.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2019-03-20
 */

#ifndef AETAS_ARGPARSE_HPP_
#define AETAS_ARGPARSE_HPP_

#include <map>
#include <string>
#include <vector>

namespace aetas {
namespace argparse {
  /**
   * @brief Parsed command line arguments container.
   *
   * This is used to hold the arguments and options after they have been parsed,
   * allowing for easy access to the values.
   */
  struct Arguments {
    /**
     * @brief Mapping from argument name to the value of the flag.
     */
    std::map<std::string, bool> flg;
    /**
     * @brief Mapping from argument name to the value of the option.
     */
    std::map<std::string, std::string> opt;
    /**
     * @brief Any unrecognized arguments.
     */
    std::vector<std::string> args;

    /**
     * @brief Converts an option to a double.
     *
     * @param arg Option name.
     *
     * @return ``double`` representation of the value in ``opt[arg]``.
     */
    inline double getf(std::string arg) { return std::atof(opt[arg].c_str()); }
    /**
     * @brief Converts an option to an integer.
     *
     * @param arg Option name.
     *
     * @return ``int`` representation of the value in ``opt[arg]``.
     */
    inline int geti(std::string arg) { return std::atoi(opt[arg].c_str()); }
  };
  /**
   * @brief Argument parser definition.
   *
   * This defines how the command line arguments should be parsed.
   */
  struct Parser {
    std::string cmd_str, usage_str, version_str;
    std::vector<std::vector<std::string>> names;
    /**
     * @brief Default values for all flags and options.
     */
    std::map<std::string, std::string> defaults;
    /**
     * @brief Help strings for all flags and options.
     */
    std::map<std::string, std::string> arg_help;
    /**
     * @brief Mapping all synonyms for an option to the option name.
     */
    std::map<std::string, std::string> opt_table;
    /**
     * @brief Mapping all synonyms for a flag to the flag name.
     */
    std::map<std::string, std::string> flag_table;
    bool help = true;
    bool version = false;

    /**
     * @brief Sets if help flag should be added.
     *
     * @param setting Setting to add help flag or not.
     */
    inline void set_help(bool setting) { help = setting; }
    /**
     * @brief Sets the usage string for help.
     *
     * @param usage Usage string to print when help is printed.
     */
    inline void set_usage(std::string usage) {
      help = true;
      usage_str = usage;
    }
    /**
     * @brief Sets the version string.
     *
     * @param ver Version string to print.
     */
    inline void set_version(std::string ver) {
      version = true;
      version_str = ver;
    }

    /**
     * @brief Add new flag to the parser.
     *
     * @param name Name[s] of the flag.
     * @param default_val Default value of the flag.
     * @param help Help message for the flag.
     */
    void add_flag(std::string name, bool default_val = false,
                  std::string help = "");
    /**
     * @brief Add new option to the parser.
     *
     * @param name Name[s] of the option.
     * @param default_val Default value of the option.
     * @param help Help message for the option.
     */
    void add_option(std::string name, std::string default_val = "",
                    std::string help = "");
  };

  /**
   * @brief Parse command line arguments.
   *
   * If help/usage/version is set, it will automatically handle ``-h``
   * ``--help`` and ``--version`` commands by printing the appropriate strings
   * defined by ``parser``.
   *
   * @param parser Parser to define how to handle inputs.
   * @param argc Number of command line arguments.
   * @param argv[] The command line arguments.
   *
   * @return ``Argument`` containing the appropriately parsed arguments.
   */
  Arguments parse_args(const Parser& parser, int argc, char* argv[]);
}  // namespace argparse
}  // namespace aetas

#endif  // AETAS_ARGPARSE_HPP_
