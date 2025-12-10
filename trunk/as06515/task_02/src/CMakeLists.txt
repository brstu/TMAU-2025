cmake_minimum_required(VERSION 3.14)
project(TemperatureModel_Rapin)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(temperature_model temperature_model.cpp)
target_include_directories(temperature_model PUBLIC .)

add_executable(temperature_app main.cpp)
target_link_libraries(temperature_app temperature_model)

add_executable(temperature_tests 
    ../test/test_temperature_model.cpp
    ../test/test_main.cpp
)
target_link_libraries(temperature_tests 
    PRIVATE temperature_model 
    gtest_main
)
target_include_directories(temperature_tests PRIVATE . ../test)

include(GoogleTest)
gtest_discover_tests(temperature_tests)

add_library(temperature_model_coverage temperature_model.cpp)
target_include_directories(temperature_model_coverage PUBLIC .)
target_compile_options(temperature_model_coverage PRIVATE -fprofile-arcs -ftest-coverage)

add_executable(temperature_tests_coverage 
    ../test/test_temperature_model.cpp
    ../test/test_main.cpp
)
target_compile_options(temperature_tests_coverage PRIVATE -fprofile-arcs -ftest-coverage)
target_link_libraries(temperature_tests_coverage 
    PRIVATE temperature_model_coverage 
    gtest_main
    gcov  
)
target_include_directories(temperature_tests_coverage PRIVATE . ../test)

find_program(GCOVR_PATH gcovr)

if(GCOVR_PATH)
    add_custom_target(coverage
        COMMAND ./temperature_tests_coverage
        COMMAND ${GCOVR_PATH} --print-summary --exclude=".*googletest.*" --exclude=".*test.*" --root=${CMAKE_SOURCE_DIR}
        COMMAND ${GCOVR_PATH} --html-nested -o coverage_report.html --exclude=".*googletest.*" --exclude=".*test.*" --root=${CMAKE_SOURCE_DIR}
        DEPENDS temperature_tests_coverage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running coverage analysis for project files only"
    )
else()
    message(WARNING "gcovr not found, coverage target will not be available")
endif()

add_custom_target(run_coverage_tests
    COMMAND ./temperature_tests_coverage
    DEPENDS temperature_tests_coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests with coverage instrumentation"
)