#include "core.hpp"

#include <memory>
#include <string>

#include "lua.hpp"

std::shared_ptr<aetas::script::ScriptCore> aetas::script::open(
    const std::string& file) {
  if (file.compare(file.length() - 4, 4, ".lua") == 0) {
    return std::make_shared<Lua>(Lua());
  }
  return std::make_shared<ScriptCore>();
}
