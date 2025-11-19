cmake_minimum_required(VERSION 3.16)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(task02_lib func.cpp)
target_include_directories(task02_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task02_app main.cpp)
target_link_libraries(task02_app PRIVATE task02_lib)

add_executable(task02_tests ../test/tests.cpp)
target_link_libraries(task02_tests PRIVATE task02_lib)

enable_testing()
add_test(NAME task02_unit_tests COMMAND task02_tests)
