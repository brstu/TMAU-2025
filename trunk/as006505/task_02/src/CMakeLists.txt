cmake_minimum_required(VERSION 3.14)
project(task_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги для покрытия кода (только для GCC/Linux)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Основная программа
add_executable(
  main
  task_02.cpp
  model.cpp
)

# Тесты
add_executable(
  runTests
  model.cpp
  ../test/testmodel.cpp
)

target_link_libraries(
  runTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)
