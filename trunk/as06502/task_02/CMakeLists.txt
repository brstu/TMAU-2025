cmake_minimum_required(VERSION 3.14)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(temperature_model src/temperature_model.cpp)
target_include_directories(temperature_model PUBLIC src)

# Основное приложение
add_executable(temperature_app src/main.cpp)
target_link_libraries(temperature_app temperature_model)

# Тесты
add_executable(temperature_tests 
    test/test_temperature_model.cpp
    test/test_main.cpp
)
target_link_libraries(temperature_tests 
    PRIVATE temperature_model 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(temperature_tests)

# Настройки для покрытия кода
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(temperature_model PRIVATE --coverage)
    target_compile_options(temperature_tests PRIVATE --coverage)
    target_link_libraries(temperature_tests PRIVATE --coverage)
endif()