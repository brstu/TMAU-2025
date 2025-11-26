cmake_minimum_required(VERSION 3.10)
project(TASK_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

enable_testing()

add_executable(as06620_task_02_main
    main.cpp
    temp_model.cpp
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(as06620_task_02_runTests
    ../test/tests.cpp
    temp_model.cpp
)

target_link_libraries(as06620_task_02_runTests GTest::GTest GTest::Main pthread)

add_test(NAME AllTests COMMAND as06620_task_02_runTests)
