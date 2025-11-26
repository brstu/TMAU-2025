cmake_minimum_required(VERSION 3.15)  
project(TMAU02 LANGUAGES CXX)  

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

add_executable(as06516_task02_main main.cpp functions.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  
)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(as06516_task02_runTests ../test/tests.cpp functions.cpp)

target_link_libraries(as06516_task02_runTests 
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main
)

target_include_directories(as06516_task02_runTests 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${googletest_SOURCE_DIR}/googletest/include
    ${googletest_SOURCE_DIR}/googlemock/include
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(as06516_task02_runTests PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(as06516_task02_runTests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(as06516_task02_runTests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
