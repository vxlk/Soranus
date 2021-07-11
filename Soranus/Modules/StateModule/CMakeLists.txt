# CMakeList.txt : CMake project for Stoinks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(StateModule
# --- includes --- #
"StateModule.hpp"
# --- includes --- #

# --- sources --- #
StateModule.cpp
# --- sources --- #
)

target_include_directories(StateModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
