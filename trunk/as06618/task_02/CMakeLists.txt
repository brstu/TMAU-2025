cmake_minimum_required(VERSION 3.16)
project(as06618_task02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(model src/model.cpp)
target_include_directories(model PUBLIC src)

add_executable(task02_app src/main.cpp)
target_link_libraries(task02_app model)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(task02_tests test/model_tests.cpp)
target_link_libraries(task02_tests model GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task02_tests)
