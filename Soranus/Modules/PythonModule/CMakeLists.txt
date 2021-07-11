# CMakeList.txt : CMake project for Soranus, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (PythonModule
# --- includes --- #
"IPythonApp.hpp"
"CPyObject.hpp"
"PyVariant.hpp"
"WrapPython.hpp"
"UnWrapPython.hpp"
# --- includes --- #

# --- sources --- #
"CPyObject.cpp"
# --- sources --- #
)

target_include_directories(PythonModule PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}\\python\\Include"
"${CMAKE_CURRENT_SOURCE_DIR}\\pybind11\\include"
)

target_link_directories(PythonModule PUBLIC
"${CMAKE_CURRENT_SOURCE_DIR}\\lib\\"
)

target_link_libraries(PythonModule PUBLIC 
"python39.lib"
)

# TODO: Add tests and install targets if needed.