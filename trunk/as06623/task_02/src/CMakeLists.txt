cmake_minimum_required(VERSION 3.10)

project(as06623_task_02)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(model_as06623 STATIC model.cpp)

add_executable(runTests_as06623 main.cpp)
target_link_libraries(runTests_as06623 model_as06623)

# Тесты
include(GoogleTest)
enable_testing()

add_executable(model_tests_as06623 ../test/model_tests.cpp)
target_link_libraries(model_tests_as06623
    model_as06623
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(model_tests_as06623)
