cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Включаем экспорт compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавляем исполняемый файл
add_executable(my_app main.cpp)

# (опционально) выводим сообщение, чтобы убедиться, что файл создаётся
message(STATUS "Compile commands will be generated in: ${CMAKE_BINARY_DIR}/compile_commands.json")