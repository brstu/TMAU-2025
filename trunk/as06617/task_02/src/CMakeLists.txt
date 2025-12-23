cmake_minimum_required(VERSION 3.16)
project(as06617_task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(as06617_task_02
    main.cpp
    func.cpp
)
target_include_directories(as06617_task_02 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# GoogleTest
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/release-1.12.1.zip
      DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Тесты
add_executable(as06617_task_02_tests
    tests.cpp
    func.cpp
)

target_include_directories(as06617_task_02_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(as06617_task_02_tests
    GTest::gtest
    GTest::gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(as06617_task_02_tests)