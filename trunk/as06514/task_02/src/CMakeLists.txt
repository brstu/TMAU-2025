cmake_minimum_required(VERSION 3.14)
project(Lab2_Testing)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги для покрытия кода
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")

# Включаем FetchContent для загрузки GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

# Для Windows устанавливаем это значение ON чтобы избежать конфликта DLL
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основная программа (если есть main.cpp)
# add_executable(main main.cpp function.cpp)

# Тестовый исполняемый файл
add_executable(
    tests
    test.cpp
    function.cpp
)

# Подключаем GoogleTest к тестам
target_link_libraries(
    tests
    GTest::gtest_main
)

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(tests)

# Цель для анализа покрытия кода
add_custom_target(
    coverage
    COMMAND $<TARGET_FILE:tests>
    COMMAND gcovr --exclude test.cpp --html --html-details -o coverage.html
    COMMAND gcovr --exclude test.cpp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS tests
    COMMENT "Running tests and generating coverage report"
)

# Утилитарные цели
add_custom_target(
    run_tests
    COMMAND $<TARGET_FILE:tests>
    DEPENDS tests
    COMMENT "Running tests"
)

add_custom_target(
    clean_coverage
    COMMAND find . -name "*.gcda" -delete
    COMMAND find . -name "*.gcno" -delete
    COMMAND rm -f coverage.html
    COMMENT "Cleaning coverage data"
)
