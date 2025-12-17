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

# Найти Google Test через find_package
find_package(GTest REQUIRED)

# Тесты
add_executable(runTests
    tests.cpp
    func.cpp
)

target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(runTests
    GTest::gtest
    GTest::gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(runTests)