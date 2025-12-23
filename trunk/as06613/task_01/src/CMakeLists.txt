cmake_minimum_required(VERSION 3.10)

project(TemperatureModelWithInterface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TemperatureModelWithInterface main.cpp)

set_target_properties(TemperatureModelWithInterface PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)