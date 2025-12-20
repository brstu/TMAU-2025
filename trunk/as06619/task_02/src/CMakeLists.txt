cmake_minimum_required(VERSION 3.10)
project(task_02)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(as06619_task_02_main as06619_task_02_mai model.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(as06619_task_02_tests ../test/test_model.cpp model.cpp)
target_link_libraries(as06619_task_02_tests GTest::gtest_main)
target_include_directories(as06619_task_02_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(as06619_task_02_tests)