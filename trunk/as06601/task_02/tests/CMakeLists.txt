enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTests_as06601 model_tests.cpp)
target_include_directories(runTests_as06601 PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(runTests_as06601 PRIVATE model GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)