#ifndef AETAS_SCRIPT_CORE_HPP_
#define AETAS_SCRIPT_CORE_HPP_

#include <array>
#include <memory>
#include <string>

namespace aetas {
namespace script {
  class ScriptCore {
   public:
    // template <typename _T>
    // _T get(const std::string& var) {
    //   return _T();
    // }

    virtual bool has_function(const std::string& func) { return false; }
    virtual bool has_string(const std::string& name) { return false; }
    virtual bool has_number(const std::string& name) { return false; }

    // template <typename _T>
    // typename std::enable_if<std::is_same<_T, void>::value, _T>::type call(
    //     const std::string& func) {
    //   return;
    // }
    // template <typename _T, typename... _ARGS>
    // typename std::enable_if<std::is_same<_T, void>::value, _T>::type call(
    //     const std::string& func, const _ARGS&... args) {
    //   return;
    // }
    // template <typename _T>
    // typename std::enable_if<!std::is_same<_T, void>::value, _T>::type call(
    //     const std::string& func) {
    //   return _T();
    // }
    // template <typename _T, typename... _ARGS>
    // typename std::enable_if<!std::is_same<_T, void>::value, _T>::type call(
    //     const std::string& func, const _ARGS&... args) {
    //   return _T();
    // }
    //
    // template <typename _T, std::size_t _R>
    // std::array<_T, _R> ncall(const std::string& func) {
    //   return std::array<_T, _R>();
    // }
    // template <typename _T, std::size_t _R, typename... _ARGS>
    // std::array<_T, _R> ncall(const std::string& func, const _ARGS&... args) {
    //   return std::array<_T, _R>();
    // }
  };

  std::shared_ptr<ScriptCore> open(const std::string& file);

  typedef std::shared_ptr<ScriptCore> Script;

}  // namespace script
}  // namespace aetas

#endif  // AETAS_SCRIPT_CORE_HPP_
