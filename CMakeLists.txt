cmake_minimum_required (VERSION 3.5)
project (TMAU)

# Search for directories simular to "trunk/as0xxyy/task_0x/src/"
# Uncomment to build all projects (for CI/CD)
# file(GLOB V_GLOB RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "trunk/as0*/*/src/")
# foreach(item ${V_GLOB})
# 	message( "Find \"${item}\"" )
# 	add_subdirectory(${item})
# endforeach()

# Build only specific student project (local development)
# add_subdirectory(trunk/as06617/task_01/src)
add_subdirectory(trunk/as06617/task_02/src)
