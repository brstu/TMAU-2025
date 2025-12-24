cmake_minimum_required(VERSION 3.10)
project(ModelSimulation_as06602 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Modeling_as06602 main.cpp model.cpp)

if (MSVC)
    target_compile_options(Modeling PRIVATE /W4 /permissive-)
else()
    target_compile_options(Modeling PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (BUILD_STRICT)
    if (MSVC)
        target_compile_options(Modeling PRIVATE /WX)
    else()
        target_compile_options(Modeling PRIVATE -Werror)
    endif()
endif()