cmake_minimum_required(VERSION 3.10)
project(Task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/*.cpp"
)

add_library(model STATIC
    t_model.cpp
)

add_executable(6604t1_main_app main.cpp)
target_link_libraries(6604t1_main_app model)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(6604t1test_model
    ${CMAKE_SOURCE_DIR}/../test/tests.cpp
)
target_link_libraries(6604t1test_model model GTest::GTest GTest::Main)

add_test(NAME test_model COMMAND 6604t1test_model)
