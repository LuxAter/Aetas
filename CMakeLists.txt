cmake_minimum_required(VERSION 3.0)
project(Aetas)

# VERSION {{{
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)
# }}}

# PACKAGES {{{
# FreeType2 {{{
find_package(Freetype)
if(FREETYPE_FOUND)
  include_directories(${FREETYPE_INCLUDE_DIRS})
  link_libraries(${FREETYPE_LIBRARIES})
endif()
# }}}
# PNG {{{
find_package(PNG)
if(PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  link_libraries(${PNG_LIBRARIES})
endif()
# }}}
# }}}

# COMPILE COMMANDS {{{
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_command.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_command.json)
endif()
# }}}

# CORE LIBRARY {{{
file(GLOB_RECURSE lib_src ${CMAKE_SOURCE_DIR} "src/*.cpp")
list(REMOVE_ITEM lib_src "${CMAKE_SOURCE_DIR}/src/main.cpp")
add_library(aetas ${lib_src})
# }}}

# CORE EXECUTABLE {{{
add_executable(aetas.exe src/main.cpp)
target_link_libraries(aetas.exe aetas)
# }}}
