# CMakeList.txt : CMake project for Stoinks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(Exchange
            INTERFACE
            "IExchange.hpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/crypto/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/stocks/")
# TODO: Add tests and install targets if needed.
