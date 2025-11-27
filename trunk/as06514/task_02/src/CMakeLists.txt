cmake_minimum_required(VERSION 3.10)
project(TMAU02)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(as06514_task02_runTests ../test/test.cpp function.cpp)
target_link_libraries(as06514_task02_runTests GTest::gtest GTest::gtest_main)

target_include_directories(as06514_task02_runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(as06514_task02_runTests)