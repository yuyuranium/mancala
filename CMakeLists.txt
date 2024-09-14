# Works with 3.14 and tested through 3.28
cmake_minimum_required(VERSION 3.14...3.28)

# Project name and a few useful settings. Other commands can pick up the results
project(
  mancala
  VERSION 0.1
  DESCRIPTION "Simple Mancala game and strategies written in C"
  LANGUAGES C)

# Always dump compile_commands.json
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)
add_subdirectory(tests)
