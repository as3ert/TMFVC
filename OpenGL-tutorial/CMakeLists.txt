cmake_minimum_required(VERSION 3.15...3.28 FATAL_ERROR)

# Project
project(opengl_tutorial
  VERSION 0.5.0
  LANGUAGES CXX)

add_subdirectory(stb_image)

# Disable in-source build
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Set a default build type if none was specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(resources)

# Dependencies
include("libs/libs.cmake")
find_package(OpenGL REQUIRED)

if (NOT assignment01)
  # Options
  option(OGL4CORE2_ENABLE_STACKTRACE "Show stacktrace on OpenGL errors (experimental)." OFF)
  
  # Core files
  set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/OGL4Core-2")
  file(GLOB_RECURSE core_source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${src_dir}/core/*.cpp" "${src_dir}/main.cpp")
  file(GLOB_RECURSE core_header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${src_dir}/core/*.h")

  # Find all plugin files
  set(plugins_dir "${src_dir}/plugins")
  file(GLOB_RECURSE plugin_source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${plugins_dir}/*.cpp")
  file(GLOB_RECURSE plugin_header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${plugins_dir}/*.h")
  file(GLOB_RECURSE plugin_shader_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${plugins_dir}/*.vert"
    "${plugins_dir}/*.tesc"
    "${plugins_dir}/*.tese"
    "${plugins_dir}/*.geom"
    "${plugins_dir}/*.frag"
    "${plugins_dir}/*.comp"
    "${plugins_dir}/*.glsl")

  # List of all files for Visual Studio
  set(all_source_files
    ${core_source_files}
    ${core_header_files}
    ${plugin_source_files}
    ${plugin_header_files}
    ${plugin_shader_files})

  # Determine plugin path relative to plugins dir
  foreach (file ${plugin_source_files} ${plugin_header_files})
    get_filename_component(file_path ${file} DIRECTORY)
    file(RELATIVE_PATH file_path_rel "/OGL4Core-2/plugins" "/${file_path}")
    set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS -DPLUGIN_DIR=\\\"${file_path_rel}\\\")
  endforeach()

  # Visual Studio file tree
  source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/OGL4Core-2" FILES ${all_source_files})

  # Disable extra console window on Windows
  set(WIN32_FLAG "")
  if (MSVC)
    option(OGL4CORE2_DISABLE_CONSOLE "Disable extra console window." OFF)
    if (OGL4CORE2_DISABLE_CONSOLE)
      set(WIN32_FLAG "WIN32")
    endif()
  endif()

  # Project
  add_executable(${PROJECT_NAME} ${WIN32_FLAG} ${all_source_files})
  target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/OGL4Core-2>)

  if (OGL4CORE2_ENABLE_STACKTRACE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE OGL4CORE2_ENABLE_STACKTRACE)
    if (WIN32)
      target_link_libraries(${PROJECT_NAME} PRIVATE Boost::stacktrace_windbg)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      target_link_libraries(${PROJECT_NAME} PRIVATE Boost::stacktrace_backtrace)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      target_link_libraries(${PROJECT_NAME} PRIVATE Boost::stacktrace_addr2line)
    elseif (UNIX)
      target_link_libraries(${PROJECT_NAME} PRIVATE Boost::stacktrace_basic)
    else()
      target_link_libraries(${PROJECT_NAME} PRIVATE Boost::stacktrace_noop)
    endif()
  endif()

  if (MSVC AND OGL4CORE2_DISABLE_CONSOLE)
    target_link_options(${PROJECT_NAME} PRIVATE "/entry:mainCRTStartup")
  endif()

  # Setup resources path
  set(plugins_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/OGL4Core-2/plugins")
  find_resource_dirs(res_dirs ${plugins_source_dir})
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.config" "PLUGINS_SOURCE_DIR=${plugins_source_dir}\n")

  # Install
  include(GNUInstallDirs)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  foreach (dir ${res_dirs})
    get_filename_component(dir_clean "${dir}" DIRECTORY)
    install(DIRECTORY "${plugins_source_dir}/${dir}/" DESTINATION "resources/${dir_clean}")
  endforeach()

  # Package
  set(OGL4CORE2_CPACK_GENERATOR "ZIP" CACHE STRING "Choose CPack generator.")
  if (UNIX)
    set_property(CACHE OGL4CORE2_CPACK_GENERATOR PROPERTY STRINGS "TGZ" "ZIP" "STGZ" "DEB")
  else()
    set_property(CACHE OGL4CORE2_CPACK_GENERATOR PROPERTY STRINGS "ZIP" "NSIS")
  endif()

  set(CPACK_GENERATOR "${OGL4CORE2_CPACK_GENERATOR}")
  set(CPACK_PACKAGE_VENDOR "Visualization Research Center (VISUS) - University of Stuttgart")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OGL4Core2 is a framework to ease the development of prototypical or education-oriented graphical algorithms.")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

  if (OGL4CORE2_CPACK_GENERATOR STREQUAL "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Visualization Research Center (VISUS) - University of Stuttgart")
    set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
    set(CPACK_SET_DESTDIR true)
    set(CPACK_INSTALL_PREFIX /opt/ogl4core2)
  elseif (OGL4CORE2_CPACK_GENERATOR STREQUAL "NSIS")
    set(CPACK_PACKAGE_EXECUTABLES "OGL4Core2;OGL4Core2")
  endif()

  # Enable strict warnings
  option(OGL4CORE2_STRICT_WARNINGS "Enable strict compiler warnings." OFF)
  if (OGL4CORE2_STRICT_WARNINGS)
    if (MSVC)
      target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    else()
      target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -pedantic -pedantic-errors)
    endif()
  endif()

  # Visual Studio folders
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  endif()

  target_link_libraries(${PROJECT_NAME} PRIVATE
    cxxopts::cxxopts
    OpenGL::GL
    glfw
    glad
    glm
    glowl
    imgui
    imguizmo
    lodepng
    datraw
    stb_image)

else()
  # Adding something we can run - Output name matches target name
  add_executable(opengl_tutorial Main.cpp Shader.cpp Texture.cpp)
  
  target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glad
    stb_image)
endif()

include(CPack)
