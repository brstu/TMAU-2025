cmake_minimum_required(VERSION 3.10)
project(ModelTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/../src)

add_executable(ModelTests test_model.cpp ../src/model.cpp)

target_link_libraries(ModelTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ModelTests)

if (MSVC)
    target_compile_options(ModelTests PRIVATE /W4 /permissive-)
else()
    target_compile_options(ModelTests PRIVATE -Wall -Wextra -Wpedantic)
endif()