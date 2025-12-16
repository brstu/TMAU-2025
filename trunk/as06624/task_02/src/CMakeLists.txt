cmake_minimum_required(VERSION 3.10)
project(task_02_yanchuk)

set(CMAKE_CXX_STANDARD 17)

add_executable(task_02_yanchuk_main
    main.cpp
    model.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../test/test_model.cpp")

    add_executable(task_02_yanchuk_tests
        ../test/test_model.cpp
        model.cpp
    )

    if(TARGET GTest::gtest)
        target_link_libraries(task_02_yanchuk_tests
            GTest::gtest GTest::gtest_main
        )
        
        target_include_directories(task_02_yanchuk_tests PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
        
        include(GoogleTest)
        gtest_discover_tests(task_02_yanchuk_tests)
    else()
        message(WARNING "GoogleTest not available, tests will not be built")
    endif()
else()
    message(WARNING "Test file not found: ${CMAKE_CURRENT_SOURCE_DIR}/../test/test_model.cpp")
endif()