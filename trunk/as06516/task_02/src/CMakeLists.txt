cmake_minimum_required(VERSION 3.15)
project(as06516_task02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(as06516_task02 main.cpp functions.cpp)
target_compile_definitions(as06516_task02 PRIVATE STANDALONE)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(as06516_task02_runTests ../test/tests.cpp functions.cpp)
target_link_libraries(as06516_task02_runTests GTest::gtest GTest::gtest_main)

target_include_directories(as06516_task02_runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(as06516_task02_runTests)
