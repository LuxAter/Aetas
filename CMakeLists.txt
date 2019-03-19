cmake_minimum_required(VERSION 3.0)
project(Iter)

# Set C/C++ Versions.
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)

# Compile Command settings.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_command.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_command.json)
endif()

# Compiles libiter.a.
file(GLOB_RECURSE lib_src ${CMAKE_SOURCE_DIR} "src/*.cpp")
list(REMOVE_ITEM lib_src "${CMAKE_SOURCE_DIR}/src/main.cpp")
add_library(iter ${lib_src})

# Compiles main test example.
add_executable(iter.exe src/main.cpp)
target_link_libraries(iter.exe iter)
