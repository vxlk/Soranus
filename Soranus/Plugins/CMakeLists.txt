# CMakeList.txt : CMake project for Soranus, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library(ComparatorPlugin
            INTERFACE
)

#set_property(TARGET ComparatorPlugin PROPERTY CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ComparatorPlugin)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libComparatorPlugin)

# TODO: Add tests and install targets if needed.
