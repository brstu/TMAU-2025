cmake_minimum_required(VERSION 3.10)
project(as06611_task_02)  # ← Изменили имя проекта

set(CMAKE_CXX_STANDARD 17)

# Main executable - добавили префикс
add_executable(as06611_main  # ← Изменили имя
    functions.cpp
    main.cpp
)

# Including Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Tests - добавили префикс
add_executable(as06611_tests  # ← Изменили имя
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/tests.cpp
    functions.cpp
)

target_link_libraries(as06611_tests
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(as06611_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GoogleTest)
gtest_discover_tests(as06611_tests)  # ← Исправили имя
