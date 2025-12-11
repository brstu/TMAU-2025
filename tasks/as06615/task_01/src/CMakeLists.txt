cmake_minimum_required (VERSION 3.5)
project (TMAU)

# Search for directories similar to "as0xxyy/task_0x/src/"
file(GLOB V_GLOB RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/")
foreach(item ${V_GLOB})
	message( "Find \"${item}\"" )
	add_subdirectory(${item})
endforeach()