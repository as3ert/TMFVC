
cmake_minimum_required(VERSION 3.28)
project(stb_image)

add_library(stb_image stb_image_impl.cpp)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_LIST_DIR})