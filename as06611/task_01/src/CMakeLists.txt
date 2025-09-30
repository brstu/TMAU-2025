cmake_minimum_required(VERSION 3.10)
project(LAB1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Генерация compile_commands.json для SonarQube
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(LAB1 LAB1t3.cpp)