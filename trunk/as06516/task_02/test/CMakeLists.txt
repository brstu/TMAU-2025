
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)


add_executable(SimulationTests test_main.cpp)

target_link_libraries(SimulationTests SimulationLib GTest::gtest_main)

target_include_directories(SimulationTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(SimulationTests)