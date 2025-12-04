cmake_minimum_required(VERSION 3.14)
project(task_01)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(as06501_main main.cpp func.cpp)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Тесты
add_executable(as06501_tests ../test/tests.cpp func.cpp)
target_link_libraries(as06501_tests GTest::gtest)
target_include_directories(as06501_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(as06501_tests)

