
add_library(SimulationLib 
    main.cpp
    functions.cpp  
)

target_include_directories(SimulationLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(MainProgram main.cpp functions.cpp)
target_compile_definitions(MainProgram PRIVATE STANDALONE)