cmake_minimum_required(VERSION 3.14)
project(task_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(COVERAGE_FLAGS "-O0 -g --coverage")


add_library(core STATIC model.cpp model.h)
target_compile_options(core PRIVATE ${COVERAGE_FLAGS})
target_link_options(core PRIVATE --coverage)


add_executable(main_exec main.cpp)
target_link_libraries(main_exec PRIVATE core)
target_compile_options(main_exec PRIVATE ${COVERAGE_FLAGS})
target_link_options(main_exec PRIVATE --coverage)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()


add_executable(tests ../test/tests.cpp)
target_link_libraries(tests PRIVATE core GTest::gtest_main)
target_compile_options(tests PRIVATE ${COVERAGE_FLAGS})
target_link_options(tests PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(tests)


find_program(GCOVR_EXECUTABLE gcovr)
if(GCOVR_EXECUTABLE)
    add_custom_target(coverage
        COMMAND ${GCOVR_EXECUTABLE}
            -r ${CMAKE_SOURCE_DIR}
            --exclude '.*_deps/.*'
            --xml coverage.xml
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage.xml for SonarQube"
    )
endif()
