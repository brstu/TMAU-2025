cmake_minimum_required(VERSION 3.10)

project(as06618_task02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(as06618_task02_lib
    model.cpp
)

target_include_directories(as06618_task02_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(as06618_task02
    main.cpp
)

target_link_libraries(as06618_task02
    as06618_task02_lib
)
