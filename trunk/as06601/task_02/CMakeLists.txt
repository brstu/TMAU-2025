cmake_minimum_required(VERSION 3.10...3.20)
project(task_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Проверяем пути
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

# Подключаем подпапки (относительно корня)
add_subdirectory(src)
add_subdirectory(tests)