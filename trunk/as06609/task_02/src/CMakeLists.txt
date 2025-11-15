cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(main main.cpp func.cpp)

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
add_executable(runTests ../test/tests.cpp func.cpp)
target_link_libraries(runTests GTest::gtest)
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests)
