add_library(model model.cpp model.h)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)
target_link_libraries(main PRIVATE model)