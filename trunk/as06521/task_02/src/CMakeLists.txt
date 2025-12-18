cmake_minimum_required(VERSION 3.14)
project(TemperatureModel_Hvisuk)

set(CMAKE_CXX_STANDARD 17)

# Настройка выходных директорий
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Включение GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(temperature_model_hvisuk temperature_model.cpp)
target_include_directories(temperature_model_hvisuk PUBLIC .)

# Основное приложение
add_executable(temperature_app_hvisuk main.cpp)
target_link_libraries(temperature_app_hvisuk temperature_model)

# Тесты
add_executable(temperature_tests_hvisuk  
    ../test/test_main.cpp
    ../test/test_temperature_model.cpp
)
target_link_libraries(temperature_tests_hvisuk  
    temperature_model_hvisuk 
    gtest_main
)
target_include_directories(temperature_tests_hvisuk PRIVATE .)

# Coverage флаги только для тестов
target_compile_options(temperature_tests_hvisuk PRIVATE --coverage)
target_link_options(temperature_tests_hvisuk PRIVATE --coverage)

# Включение тестов в CTest
include(GoogleTest)
gtest_discover_tests(temperature_tests_hvisuk)

# Простая цель для coverage
add_custom_target(coverage
    COMMAND echo "=== Running tests to generate coverage data ==="
    COMMAND ${CMAKE_BINARY_DIR}/bin/temperature_tests_hvisuk || echo "Tests completed"
    COMMAND echo "=== Generating coverage report ==="
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} 
        --filter="src/.*\.cpp$" 
        --exclude=".*test.*" 
        --exclude=".*googletest.*" 
        --print-summary
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} 
        --filter="src/.*\.cpp$" 
        --exclude=".*test.*" 
        --exclude=".*googletest.*" 
        --html -o coverage_report.html
    COMMAND echo "Coverage report generated: ${CMAKE_BINARY_DIR}/coverage_report.html"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating coverage report"
)

# Цель для быстрого просмотра coverage
add_custom_target(coverage_summary
    COMMAND echo "=== Coverage summary ==="
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} 
        --filter="src/.*\.cpp$" 
        --exclude=".*test.*" 
        --exclude=".*googletest.*" 
        --print-summary
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Showing coverage summary"
)