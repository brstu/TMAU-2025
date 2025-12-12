cmake_minimum_required(VERSION 3.16)
project(task_01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Приложение
add_executable(TMAU_as06603 TMAU_06603.cpp)
target_include_directories(TMAU_as06603 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
