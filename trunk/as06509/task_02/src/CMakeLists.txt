cmake_minimum_required(VERSION 3.10)
project(Task02)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(main src/main.cpp src/model.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(BUILD_GMOCK OFF)
set(BUILD_GTEST ON)
set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests test/test_model.cpp src/model.cpp)
target_include_directories(runTests PRIVATE src)
target_link_libraries(runTests gtest gtest_main)

add_test(NAME RunTests COMMAND runTests)
