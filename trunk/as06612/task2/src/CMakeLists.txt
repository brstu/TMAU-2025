cmake_minimum_required(VERSION 3.16)
project(TMAU_task2_06612)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main_06612 main.cpp func.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests_06612 ../test/test.cpp func.cpp)
target_link_libraries(tests_06612 PRIVATE gtest gtest_main)
target_include_directories(tests_06612 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(tests_06612)