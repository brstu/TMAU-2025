cmake_minimum_required (VERSION 3.5)
project (TMAU)

# Search for directories similar to "trunk/as0xxyy/task_0x/src/"
file(GLOB V_GLOB RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "trunk/as06615/task_01/src/")
foreach(item ${V_GLOB})
	message( "Find \"${item}\"" )
	add_subdirectory(${item})
endforeach()