cmake_minimum_required(VERSION 3.10)
project(task_02_as06515)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0079 NEW)

# --- Настройка Google Test ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Сборка тестового исполняемого файла ---
add_executable(runTests_as06515 ../test/test.cpp module.cpp)
add_executable(main_as06515 main.cpp module.cpp)

# Установка опций покрытия для GCC/Clang для ОБОИХ целей
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Для тестов
    target_compile_options(runTests_as06515 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(runTests_as06515 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
    
    # Для main (если нужно)
    target_compile_options(main_as06515 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -g 
        -O0
    )
    target_link_options(main_as06515 PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )
endif()

target_link_libraries(runTests_as06515 gtest gtest_main)
target_include_directories(runTests_as06515 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(runTests_as06515)