cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
  opengl_tutorial
  VERSION 1.0
  LANGUAGES CXX)

add_subdirectory(glad)
add_subdirectory(stb_image)

# Find packages 
find_package(OpenGL REQUIRED)
IF (WIN32)
  add_subdirectory(glfw)
ELSE()
  find_package(glfw3)
ENDIF()

include_directories(${OPENGL_INCLUDE_DIR})

# Adding something we can run - Output name matches target name
add_executable(opengl_tutorial Main.cpp Shader.cpp Texture.cpp)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(opengl_tutorial ${OPENGL_gl_LIBRARY} glfw glad stb_image)