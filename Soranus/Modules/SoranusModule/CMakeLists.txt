# CMakeList.txt : CMake project for Stoinks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(SoranusModule
# --- includes --- #
"SoranusModule.hpp"
# --- includes --- #

# --- sources --- #
SoranusModule.cpp
# --- sources --- #
)

target_include_directories(SoranusModule PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(SoranusModule PUBLIC 
ThreadModule
)
