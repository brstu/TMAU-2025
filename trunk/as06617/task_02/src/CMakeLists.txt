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

# Тесты
add_executable(runTests
    tests.cpp
    func.cpp
)

# Пути Homebrew GTest
target_include_directories(runTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    /usr/local/include
)
target_link_libraries(runTests
    /usr/local/lib/libgtest.a
    /usr/local/lib/libgtest_main.a
    pthread
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(runTests)
