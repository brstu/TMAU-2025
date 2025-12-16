cmake_minimum_required(VERSION 3.10)
project(task_02_67)

set(CMAKE_CXX_STANDARD 17)

add_executable(main67 runMain.cpp func.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(runTests67 ../test/runTests.cpp func.cpp)
target_link_libraries(runTests67 GTest::gtest GTest::gtest_main)

target_include_directories(runTests67 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests67)
