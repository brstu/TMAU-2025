find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../src)

add_executable(test_models test_models.cpp ../src/models.cpp)
target_link_libraries(test_models GTest::GTest GTest::Main)

add_test(NAME ModelTests COMMAND test_models)
