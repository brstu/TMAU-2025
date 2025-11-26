cmake_minimum_required(VERSION 3.10)
project(as06516_task02 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "*.c"
    "*.cc"
    "*.cpp"
    "*.cxx"
)

list(FILTER SOURCES EXCLUDE REGEX "test_main\\.cpp$")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found for the main program.")
endif()

add_executable(task02 ${SOURCES})


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")

    enable_testing()

    add_subdirectory(${CMAKE_BINARY_DIR}/_deps/googletest-src
                     ${CMAKE_BINARY_DIR}/_deps/googletest-build
                     EXCLUDE_FROM_ALL)

    add_executable(task02_tests test_main.cpp)

    target_link_libraries(task02_tests
        PRIVATE
            gtest
            gtest_main
            pthread
    )

    add_test(NAME task02_run_tests COMMAND task02_tests)

else()
    message(STATUS "Warning: test_main.cpp not found — tests disabled.")
endif()
