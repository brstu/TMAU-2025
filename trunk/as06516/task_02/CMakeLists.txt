cmake_minimum_required(VERSION 3.15) 
project(Task02_Simulation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MainProgram 
    src/main.cpp
    src/functions.cpp
)

enable_testing()

add_executable(SimulationTests 
    test/test_main.cpp
    src/functions.cpp
)

target_include_directories(SimulationTests PRIVATE src)

find_package(GTest)
if(GTest_FOUND)
    target_link_libraries(SimulationTests GTest::gtest GTest::gtest_main)
else()
    
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fdab60b14b31b89d3c2f60.zip
    )
    FetchContent_MakeAvailable(googletest)
    target_link_libraries(SimulationTests gtest gtest_main)
endif()

add_test(NAME SimulationTests COMMAND SimulationTests)
