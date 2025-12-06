cmake_minimum_required(VERSION 3.16...3.31)
project(TMAU_02_task06616)

set(CMAKE_CXX_STANDARD 17)

add_executable(task2_exe main.cpp func.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Тестовый исполняемый файл для task2
add_executable(runTests_task2 ../test/test.cpp func.cpp)

target_link_libraries(runTests_task2 GTest::gtest GTest::gtest_main)
target_include_directories(runTests_task2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests_task2)
