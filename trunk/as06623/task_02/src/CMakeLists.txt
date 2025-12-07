cmake_minimum_required(VERSION 3.10)

project(as06623_task_02)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------
# Библиотека модели
# ------------------
add_library(model_as06623 STATIC
    model.cpp
)

# Заголовки лежат в текущей папке src
target_include_directories(model_as06623 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ------------------
# Основное приложение
# ------------------
add_executable(run_model_as06623
    main.cpp
)

target_link_libraries(run_model_as06623
    model_as06623
)

# ------------------
# GoogleTest
# ------------------
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ------------------
# Тесты
# ------------------
add_executable(model_tests_as06623
    ../test/model_tests.cpp
)

target_link_libraries(model_tests_as06623
    model_as06623
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(model_tests_as06623)
