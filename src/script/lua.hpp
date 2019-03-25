#ifndef AETAS_SCRIPT_LUA_HPP_
#define AETAS_SCRIPT_LUA_HPP_

// TODO
// #ifdef AETAS_LUA
extern "C" {
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
}

#include <array>
#include <functional>
#include <string>
#include <vector>

#include "core.hpp"

#include "../std/vector.hpp"

namespace aetas {
namespace script {
  class Lua : public ScriptCore {
   public:
    Lua();
    explicit Lua(const std::string& file_path);
    Lua(const Lua& copy);

    ~Lua();

    template <typename _T>
    _T get(const std::string& var) {
      if (!state_) return _T();
      _T result;
      int level;
      if ((level = lua_get_to_stack(var)) != -1) {
        result = lua_get<_T>();
        lua_pop(state_, level + 1);
      } else {
        result = _T();
      }
      return result;
    }

    bool has_function(const std::string& func);
    bool has_string(const std::string& name);
    bool has_number(const std::string& name);

    template <typename _T>
    typename std::enable_if<!std::is_same<_T, void>::value, _T>::type call(
        const std::string& func) {
      lua_get_to_stack(func);
      if (!lua_isfunction(state_, -1)) {
        return _T();
      }
      lua_call(state_, 0, 1);
      return lua_get<_T>();
    }

    template <typename _T, typename... _ARGS>
    typename std::enable_if<!std::is_same<_T, void>::value, _T>::type call(
        const std::string& func, const _ARGS&... args) {
      lua_get_to_stack(func);
      if (!lua_isfunction(state_, -1)) {
        return _T();
      }
      call<0, 1>(args...);
      return lua_get<_T>();
    }

    template <typename _T>
    typename std::enable_if<std::is_same<_T, void>::value, _T>::type call(
        const std::string& func) {
      lua_get_to_stack(func);
      if (!lua_isfunction(state_, -1)) {
        return;
      }
      lua_call(state_, 0, 0);
    }
    template <typename _T, typename... _ARGS>
    typename std::enable_if<std::is_same<_T, void>::value, _T>::type call(
        const std::string& func, const _ARGS&... args) {
      lua_get_to_stack(func);
      if (!lua_isfunction(state_, -1)) {
        return _T();
      }
      call<0, 0>(args...);
    }

    template <typename _T, std::size_t _R>
    std::array<_T, _R> ncall(const std::string& func) {
      lua_get_to_stack(func);
      if (!lua_isfunction(state_, -1)) {
        return std::array<_T, _R>{{}};
      }
      lua_call(state_, 0, _R);
      std::array<_T, _R> ret;
      for (std::size_t i = 0; i < _R; ++i) {
        ret[i] = lua_get<_T>();
      }
      return ret;
    }

    template <typename _T, std::size_t _R, typename... _ARGS>
    std::array<_T, _R> ncall(const std::string& func, const _ARGS&... args) {
      lua_get_to_stack(func);
      if (!lua_isfunction(state_, -1)) {
        return std::array<_T, _R>{{}};
      }
      call<0, _R>(args...);
      std::array<_T, _R> ret;
      for (int i = (int)_R - 1; i >= 0; --i) {
        ret[i] = lua_get<_T>();
      }
      return ret;
    }

   protected:
    int lua_get_to_stack(const std::string& var_name);

    template <typename _T>
    typename std::enable_if<std::is_arithmetic<_T>::value, void>::type lua_push(
        const _T& v) {
      lua_pushnumber(state_, v);
    }
    template <typename _T>
    typename std::enable_if<std::is_same<_T, std::string>::value, void>::type
    lua_push(const _T& v) {
      lua_pushstring(state_, v.c_str());
    }
    template <typename _T>
    typename std::enable_if<std::is_vector<_T>::value, void>::type lua_push(
        const _T& v) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_push(i + 1);
        lua_push(v[i]);
        lua_settable(state_, -3);
      }
    }

    template <typename _T>
    typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type lua_get(
        const int pos = -1) {
      if (lua_isnil(state_, pos)) {
        return _T();
      } else {
        _T val = static_cast<_T>(lua_tonumber(state_, pos));
        lua_pop(state_, 1);
        return val;
      }
    }
    template <typename _T>
    typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
    lua_get(const int pos = -1) {
      if (lua_isnil(state_, pos)) {
        return _T();
      } else {
        _T val = _T(lua_tostring(state_, pos));
        lua_pop(state_, 1);
        return val;
      }
    }
    template <typename _T>
    typename std::enable_if<std::is_vector<_T>::value, _T>::type lua_get(
        const int pos = -1) {
      if (lua_isnil(state_, pos)) {
        return _T();
      } else {
        _T vec;
        lua_pushnil(state_);
        while (lua_next(state_, pos - 1)) {
          vec.push_back(lua_get<typename _T::value_type>());
          lua_pop(state_, 1);
        }
        int n = lua_gettop(state_);
        lua_pop(state_, n);
        return vec;
      }
    }

    template <std::size_t _N, std::size_t _R, typename _U>
    inline void call(const _U& v) {
      lua_push(v);
      lua_call(state_, _N + 1, _R);
    }
    template <std::size_t _N, std::size_t _R, typename _U, typename... _ARGS>
    inline void call(const _U& v, const _ARGS&... args) {
      lua_push(v);
      call<_N + 1, _R>(args...);
    }

   private:
    lua_State* state_;
  };
}  // namespace script
}  // namespace aetas
// #endif

#endif  // AETAS_SCRIPT_LUA_HPP_
