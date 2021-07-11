cmake_minimum_required(VERSION 3.10)

add_library(FTXExchange 
"FTXExchangeExports.hpp" 
"FTXExchange.hpp" 
"FTXExchange.cpp")

target_include_directories(FTXExchange PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/../../ #Exchange directory
${CMAKE_CURRENT_SOURCE_DIR}/../../../Modules/PythonModule #Python Module directory
)

target_link_libraries(FTXExchange PUBLIC PythonModule)
