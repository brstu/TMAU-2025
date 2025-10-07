cmake_minimum_required(VERSION 3.5)

project(tmau)

add_executable (TMAU1 tmau.cpp)
if (WIN32)
    add_compile_options(/utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()