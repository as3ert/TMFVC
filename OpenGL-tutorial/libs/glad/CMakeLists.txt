# cmake_minimum_required(VERSION 3.28)
# project(Glad)



cmake_minimum_required(VERSION 3.15...3.28 FATAL_ERROR)

project(glad C)

if (NOT assignment01)
add_library(glad
  include/glad/gl.h
  include/KHR/khrplatform.h
  src/gl.c)
target_include_directories(glad PUBLIC include/)
target_link_libraries(glad ${CMAKE_DL_LIBS})
else()
add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
endif()

set_target_properties(glad PROPERTIES
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
