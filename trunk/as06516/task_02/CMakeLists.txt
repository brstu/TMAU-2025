cmake_minimum_required(VERSION 3.15)
project(SimulationProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем тестирование
enable_testing()

# Добавляем поддиректории
add_subdirectory(src)
add_subdirectory(test)