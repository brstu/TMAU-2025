cmake_minimum_required(VERSION 3.14)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 17)

# Включение GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(temperature_model temperature_model.cpp)
target_include_directories(temperature_model PUBLIC .)  # Текущая папка

# Основное приложение
add_executable(temperature_app main.cpp)
target_link_libraries(temperature_app temperature_model)

# Тесты - используем относительные пути к папке test
add_executable(temperature_tests 
    ../test/test_temperature_model.cpp
    ../test/test_main.cpp
)
target_link_libraries(temperature_tests 
    PRIVATE temperature_model 
    gtest_main
)
# Для тестов нужно указать include директории
target_include_directories(temperature_tests PRIVATE .)  # Текущая папка (src)

include(GoogleTest)
gtest_discover_tests(temperature_tests)

# Отдельная библиотека для coverage
add_library(temperature_model_coverage temperature_model.cpp)
target_include_directories(temperature_model_coverage PUBLIC .)
target_compile_options(temperature_model_coverage PRIVATE -fprofile-arcs -ftest-coverage)

# Тесты с покрытием
add_executable(temperature_tests_coverage 
    ../test/test_temperature_model.cpp
    ../test/test_main.cpp
)
target_link_libraries(temperature_tests_coverage 
    PRIVATE temperature_model_coverage 
    gtest_main 
    -lgcov
)
target_include_directories(temperature_tests_coverage PRIVATE .)

# Цель для coverage анализа
add_custom_target(coverage
    COMMAND ./temperature_tests_coverage
    COMMAND gcovr --print-summary --exclude=".*googletest.*" --exclude=".*test.*" --root=..
    COMMAND gcovr --html-nested -o coverage_report.html --exclude=".*googletest.*" --exclude=".*test.*" --root=..
    DEPENDS temperature_tests_coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running coverage analysis for project files only"
)