# CMakeList.txt : CMake project for Stoinks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

# Add interface files here
add_library(Interfaces
INTERFACE
"ISoranus.hpp"
)
