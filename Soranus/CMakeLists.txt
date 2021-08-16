# CMakeList.txt : CMake project for Soranus, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Exchange)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Interface)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Modules)

# Add source to this project's executable.
add_executable (Soranus
# --- includes --- #
"Soranus.hpp"
# --- includes --- #

# --- sources --- #
"Soranus.cpp" 
# --- sources --- #
)

#set_property(TARGET Soranus PROPERTY CXX_STANDARD 20)

target_include_directories(Soranus PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
# Module include directories
${CMAKE_CURRENT_SOURCE_DIR}/Modules
${CMAKE_CURRENT_SOURCE_DIR}/Modules/ThreadModule
${CMAKE_CURRENT_SOURCE_DIR}/Modules/PluginModule
${CMAKE_CURRENT_SOURCE_DIR}/Modules/SoranusModule
)

target_link_libraries(Soranus PUBLIC 
FTXExchange
SoranusModule
)

# TODO: Add tests and install targets if needed.
