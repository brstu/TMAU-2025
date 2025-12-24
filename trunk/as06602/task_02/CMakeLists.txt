cmake_minimum_required(VERSION 3.10)
project(Modeling)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Find Google Test
find_package(GTest REQUIRED)

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/model.cpp
)

# Test executable
add_executable(test_model
    test/test_model.cpp
    ${SOURCES}
)

# Link Google Test
target_link_libraries(test_model GTest::gtest_main)

# Enable testing
enable_testing()
add_test(NAME test_model COMMAND test_model)