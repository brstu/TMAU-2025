cmake_minimum_required(VERSION 3.16)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(main
    main.cpp
    func.cpp
)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

# Тесты
add_executable(runTests
    tests.cpp
    func.cpp
)
target_link_libraries(runTests
    GTest::gtest
    GTest::gtest_main
    pthread
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(runTests)
