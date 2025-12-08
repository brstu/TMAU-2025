enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTests model_tests.cpp)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/srs)
target_link_libraries(runTests PRIVATE model GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)