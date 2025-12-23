cmake_minimum_required(VERSION 3.10)

project(lab2_as06625 LANGUAGES CXX)

add_executable(CMakeProject2
    CMakeProject2.cpp
    CMakeProject2.h
)

set_property(TARGET CMakeProject2 PROPERTY CXX_STANDARD 20)
set_property(TARGET CMakeProject2 PROPERTY CXX_STANDARD_REQUIRED ON)
