# CMakeList.txt : CMake project for Stoinks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(Modules
            INTERFACE
)

# Add your modules here
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/SoranusModule/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThreadModule/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/StateModule/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/PythonModule/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/JsonModule/")
