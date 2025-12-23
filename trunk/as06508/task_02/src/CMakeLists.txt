cmake_minimum_required(VERSION 3.31.6)
project(task_02 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force UTF-8 for MSVC compiler
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Main program executable
add_executable(main_as06508 main.cpp func.cpp)

# Connecting GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Executable file for tests
add_executable(runTests_as06508 func.cpp ../test/tests.cpp)

target_link_libraries(runTests_as06508 GTest::gtest_main)
target_include_directories(runTests_as06508 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Automatic test detection
include(GoogleTest)
gtest_discover_tests(runTests_as06508)





