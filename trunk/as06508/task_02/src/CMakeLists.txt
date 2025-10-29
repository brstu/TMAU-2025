cmake_minimum_required(VERSION 3.14)
project(task_02 LANGUAGES CXX)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Принудительно UTF-8 для компилятора MSVC
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Исполняемый файл программы
add_executable(main main.cpp func.cpp)

# Подключение GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включаем тестирование
enable_testing()

# Исполняемый файл для тестов
add_executable(runTests tests.cpp func.cpp)
target_link_libraries(runTests GTest::gtest_main)
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(runTests)