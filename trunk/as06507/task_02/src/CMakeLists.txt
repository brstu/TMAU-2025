cmake_minimum_required(VERSION 3.10)
project(ModelSimulationTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} --coverage")

set(SRC_FILES
    model.cpp
)

# add_executable(simulator model.cpp main.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(as06507_task_02_run_tests
    ../test/tests.cpp
    ${SRC_FILES}
)

target_link_libraries(as06507_task_02_run_tests
    GTest::GTest
    GTest::Main
    pthread
)

enable_testing()
add_test(NAME ModelUnitTests COMMAND as06507_task_02_run_tests)
