
add_executable (CMakeProject2 "CMakeProject2.cpp" "CMakeProject2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject2 PROPERTY CXX_STANDARD 20)
endif()


