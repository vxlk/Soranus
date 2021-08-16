# CMakeList.txt : CMake project for Stoinks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(PluginModule
# --- includes --- #
"IPlugin.hpp"
"PluginCollection.hpp"
"FeatureConfiguration.hpp"
"PluginModule.hpp"
# --- includes --- #

# --- sources --- #
"PluginCollection.cpp"
"FeatureConfiguration.cpp"
# --- sources --- #
)

target_include_directories(PluginModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
