cmake_minimum_required(VERSION 3.28)
project(GLFW)

add_library(GLFW lib/glfw3.lib)
set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GLFW PUBLIC include/GLFW)