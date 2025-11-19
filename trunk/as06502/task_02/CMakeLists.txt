cmake_minimum_required(VERSION 3.14)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 17)

# подкачка и юз googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(temperature_model src/temperature_model.cpp)
target_include_directories(temperature_model PUBLIC src)

add_executable(temperature_app src/main.cpp)
target_link_libraries(temperature_app temperature_model)

add_executable(temperature_tests test/test_temperature_model.cpp test/test_main.cpp)
target_link_libraries(temperature_tests PRIVATE temperature_model gtest_main)

include(GoogleTest)
gtest_discover_tests(temperature_tests)

# библиотека для coverage
add_library(temperature_model_coverage src/temperature_model.cpp)
target_include_directories(temperature_model_coverage PUBLIC src)
target_compile_options(temperature_model_coverage PRIVATE -fprofile-arcs -ftest-coverage)

# тесты с покрытием
add_executable(temperature_tests_coverage test/test_temperature_model.cpp test/test_main.cpp)
target_link_libraries(temperature_tests_coverage PRIVATE temperature_model_coverage gtest_main -lgcov)

# цель для coverage с правильными фильтрами
add_custom_target(coverage
    COMMAND ./temperature_tests_coverage
    COMMAND gcovr --print-summary --exclude=".*googletest.*" --exclude=".*test.*" --root=..
    COMMAND gcovr --html-nested -o coverage_report.html --exclude=".*googletest.*" --exclude=".*test.*" --root=..
    DEPENDS temperature_tests_coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running coverage analysis for project files only"
)
