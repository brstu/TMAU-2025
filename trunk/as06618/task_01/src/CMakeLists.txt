cmake_minimum_required(VERSION 3.18)
project(thermal_simulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sim
    main.cpp
)
