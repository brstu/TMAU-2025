cmake_minimum_required(VERSION 3.14)
project(task_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()


add_library(core STATIC
    model.cpp
    model.h
)

add_executable(main_exec main.cpp)
target_link_libraries(main_exec PRIVATE core)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(tests ../test/tests.cpp)
target_link_libraries(tests PRIVATE core gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

add_custom_target(coverage
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR}
            --exclude '.*_deps/.*'
            --xml coverage.xml
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

