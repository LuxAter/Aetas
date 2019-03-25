#include "lua.hpp"

// TODO
// #ifdef AETAS_LUA
extern "C" {
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
}

#include <string>

aetas::script::Lua::Lua() {}
aetas::script::Lua::Lua(const std::string& file_path) {
  state_ = luaL_newstate();
  luaL_openlibs(state_);
  if (luaL_loadfile(state_, file_path.c_str()) || lua_pcall(state_, 0, 0, 0)) {
    state_ = nullptr;
  }
}
aetas::script::Lua::Lua(const Lua& copy){
  state_ = copy.state_;
}
aetas::script::Lua::~Lua() {
  if (state_ != nullptr) {
    // lua_close(state_);
    // state_ = nullptr;
  }
}

bool aetas::script::Lua::has_function(const std::string& func) {
  lua_getglobal(state_, func.c_str());
  bool val = lua_isfunction(state_, -1);
  lua_pop(state_, -1);
  return val;
}
bool aetas::script::Lua::has_string(const std::string& name) {
  lua_getglobal(state_, name.c_str());
  bool val = lua_isstring(state_, -1);
  lua_pop(state_, -1);
  return val;
}
bool aetas::script::Lua::has_number(const std::string& name) {
  lua_getglobal(state_, name.c_str());
  bool val = lua_isnumber(state_, -1);
  lua_pop(state_, -1);
  return val;
}

int aetas::script::Lua::lua_get_to_stack(const std::string& var_name) {
  int level = 0;
  std::string var = "";
  for (unsigned i = 0; i < var_name.size(); ++i) {
    if (var_name.at(i) == '.') {
      if (level == 0) {
        lua_getglobal(state_, var.c_str());
      } else {
        lua_getfield(state_, -1, var.c_str());
      }

      if (lua_isnil(state_, -1)) {
        return -1;
      } else {
        var = "";
        level++;
      }
    } else {
      var += var_name.at(i);
    }
  }
  if (level == 0) {
    lua_getglobal(state_, var.c_str());

  } else {
    lua_getfield(state_, -1, var.c_str());
  }
  if (lua_isnil(state_, -1)) {
    return -1;
  }
  return level;
}

// #endif
