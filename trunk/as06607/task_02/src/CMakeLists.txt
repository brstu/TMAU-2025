cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(model
    model.cpp
)

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(as06607_task_02_tests
    ../test/tests.cpp
)

target_link_libraries(as06607_task_02_tests
    model
    gtest
    gtest_main
)

enable_testing()
add_test(NAME model_tests COMMAND as06607_task_02_tests)
