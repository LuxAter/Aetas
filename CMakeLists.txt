cmake_minimum_required(VERSION 3.0)
project(Aetas)

# VERSION {{{
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)
# }}}

# PACKAGES {{{
# Varia {{{
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/varia")
include_directories("${Varia_SOURCE_DIR}/include/")
# }}}
# PThread {{{
find_package(Threads)
if (THREADS_FOUND)
  link_libraries(${CMAKE_THREAD_LIBS_INIT})
endif()
# }}}
# }}}

# DOCUMENTATION {{{
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_LATEX YES)
  doxygen_add_docs(docs ${PROJECT_SOURCE_DIR})
endif()
# }}}

# RESOURCE FILES {{{
file(GLOB_RECURSE resource_src ${CMAKE_SOURCE_DIR} "resources/*")
message(${resource_src})
file(COPY ${resource_src} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
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
target_link_libraries(aetas.exe aetas varia)
# }}}
