cmake_minimum_required(VERSION 3.15)

project(as06625_task02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core
    functions.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(as06625_task02 main.cpp)
target_link_libraries(as06625_task02 core)
target_compile_definitions(as06625_task02 PRIVATE STANDALONE)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(as06625_task02_runTests ../test/tests.cpp)
target_link_libraries(as06625_task02_runTests core GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(as06625_task02_runTests)
