cmake_minimum_required(VERSION 3.10)
project(ControlSystemsLab)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(control_systems_main main.cpp function.cpp)

# Загрузка GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Тестовый исполняемый файл
add_executable(control_systems_tests test.cpp function.cpp)
target_link_libraries(control_systems_tests GTest::gtest GTest::gtest_main)

# Добавляем include директории для тестов
target_include_directories(control_systems_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(control_systems_tests)

# Дополнительная цель для удобного запуска тестов
add_custom_target(run_all_tests
    COMMAND control_systems_tests
    DEPENDS control_systems_tests
    COMMENT "Running all tests for Control Systems Lab"
)