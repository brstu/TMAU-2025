cmake_minimum_required(VERSION 3.14)
project(task_01)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(as06505_main main.cpp func.cpp)

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
add_executable(as06505_tests ../test/tests.cpp func.cpp)
target_link_libraries(as06505_tests GTest::gtest)
target_include_directories(as06505_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(as06505_tests)

