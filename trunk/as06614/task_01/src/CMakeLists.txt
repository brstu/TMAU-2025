cmake_minimum_required(VERSION 3.10)

project(temperature_model LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
    add_compile_options(/utf-8)
endif()

add_executable(temperature_model main.cpp)

set_target_properties(temperature_model PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(temperature_model PRIVATE 
        -Wall
        -Wextra
        -Wpedantic
    )
endif()