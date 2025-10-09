cmake_minimum_required(VERSION 3.10)
project(ModelSimulation LANGUAGES CXX)

# Используем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавляем исполняемый файл
add_executable(Modeling main.cpp)

# --- Настройки предупреждений ---
# Включаем общие предупреждения компилятора
if (MSVC)
    target_compile_options(Modeling PRIVATE /W4 /permissive-)
else()
    target_compile_options(Modeling PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- Опционально для CI ---
# Если активирована переменная BUILD_STRICT, включаем -Werror
# (можно задать при запуске: cmake -DBUILD_STRICT=ON ..)
if (BUILD_STRICT)
    if (MSVC)
        target_compile_options(ModelSimulation PRIVATE /WX)
    else()
        target_compile_options(ModelSimulation PRIVATE -Werror)
    endif()
endif()