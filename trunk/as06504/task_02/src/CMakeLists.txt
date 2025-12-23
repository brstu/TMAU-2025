cmake_minimum_required(VERSION 3.10)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -O0 --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_library(matew2005_2_model model.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matew2005_2_tests ../test/tests.cpp)
target_link_libraries(matew2005_2_tests matew2005_2_model gtest_main)

add_test(NAME RunTests COMMAND matew2005_2_tests)
