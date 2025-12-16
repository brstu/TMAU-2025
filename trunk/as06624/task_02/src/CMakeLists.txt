cmake_minimum_required(VERSION 3.16)

project(TMAU_02_task06624 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(task2_exe_06624
    main.cpp
    model.cpp
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(runTests_task02_06624
    ${CMAKE_CURRENT_LIST_DIR}/../test/test_model.cpp
    model.cpp
)

target_link_libraries(runTests_task02_06624
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(runTests_task02_06624 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
