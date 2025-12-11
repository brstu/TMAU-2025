cmake_minimum_required(VERSION 3.16)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../test)

# Приложение
add_executable(main_as06603
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/func.cpp
)
target_include_directories(main_as06603 PRIVATE ${SRC_DIR})

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
add_executable(runTests_as06603
    ${TEST_DIR}/tests.cpp
    ${SRC_DIR}/func.cpp
)
target_include_directories(runTests_as06603 PRIVATE ${SRC_DIR})
target_link_libraries(runTests_as06603 GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests_as06603)