cmake_minimum_required(VERSION 3.16)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Приложение
add_executable(as06622_main main.cpp func.cpp)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(as06622_tests ../test/tests.cpp func.cpp)
target_include_directories(as06622_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(as06622_tests GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(as06622_tests)