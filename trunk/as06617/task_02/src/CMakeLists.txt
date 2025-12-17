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

# Попытаться найти Google Test локально
find_package(GTest QUIET)

# Если не найден - загрузить автоматически
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/release-1.12.1.zip
      DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    # Создаём алиасы для совместимости
    add_library(GTest::gtest ALIAS gtest)
    add_library(GTest::gtest_main ALIAS gtest_main)
endif()

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