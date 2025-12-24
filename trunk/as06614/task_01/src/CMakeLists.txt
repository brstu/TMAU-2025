cmake_minimum_required(VERSION 3.10)

project(TemperatureModel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TemperatureModel main.cpp)

set_target_properties(TemperatureModel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)