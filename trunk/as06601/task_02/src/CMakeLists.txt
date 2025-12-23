add_library(model model.cpp model.h)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_as06601 main.cpp)
target_link_libraries(main_as06601 PRIVATE model)