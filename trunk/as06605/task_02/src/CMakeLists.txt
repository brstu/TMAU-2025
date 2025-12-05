cmake_minimum_required(VERSION 3.16)
project(tmau_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(as06605_main main.cpp function.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(as06605_tests ../test/tests.cpp function.cpp)
target_link_libraries(as06605_tests GTest::gtest GTest::gtest_main)

target_include_directories(as06605_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(as06605_tests)
