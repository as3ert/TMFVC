# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build

# Include any dependencies generated for this target.
include CMakeFiles/opengl_tutorial.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/opengl_tutorial.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/opengl_tutorial.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opengl_tutorial.dir/flags.make

CMakeFiles/opengl_tutorial.dir/Main.cpp.o: CMakeFiles/opengl_tutorial.dir/flags.make
CMakeFiles/opengl_tutorial.dir/Main.cpp.o: /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Main.cpp
CMakeFiles/opengl_tutorial.dir/Main.cpp.o: CMakeFiles/opengl_tutorial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opengl_tutorial.dir/Main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_tutorial.dir/Main.cpp.o -MF CMakeFiles/opengl_tutorial.dir/Main.cpp.o.d -o CMakeFiles/opengl_tutorial.dir/Main.cpp.o -c /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Main.cpp

CMakeFiles/opengl_tutorial.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/opengl_tutorial.dir/Main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Main.cpp > CMakeFiles/opengl_tutorial.dir/Main.cpp.i

CMakeFiles/opengl_tutorial.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/opengl_tutorial.dir/Main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Main.cpp -o CMakeFiles/opengl_tutorial.dir/Main.cpp.s

CMakeFiles/opengl_tutorial.dir/Shader.cpp.o: CMakeFiles/opengl_tutorial.dir/flags.make
CMakeFiles/opengl_tutorial.dir/Shader.cpp.o: /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Shader.cpp
CMakeFiles/opengl_tutorial.dir/Shader.cpp.o: CMakeFiles/opengl_tutorial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/opengl_tutorial.dir/Shader.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_tutorial.dir/Shader.cpp.o -MF CMakeFiles/opengl_tutorial.dir/Shader.cpp.o.d -o CMakeFiles/opengl_tutorial.dir/Shader.cpp.o -c /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Shader.cpp

CMakeFiles/opengl_tutorial.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/opengl_tutorial.dir/Shader.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Shader.cpp > CMakeFiles/opengl_tutorial.dir/Shader.cpp.i

CMakeFiles/opengl_tutorial.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/opengl_tutorial.dir/Shader.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Shader.cpp -o CMakeFiles/opengl_tutorial.dir/Shader.cpp.s

CMakeFiles/opengl_tutorial.dir/Texture.cpp.o: CMakeFiles/opengl_tutorial.dir/flags.make
CMakeFiles/opengl_tutorial.dir/Texture.cpp.o: /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Texture.cpp
CMakeFiles/opengl_tutorial.dir/Texture.cpp.o: CMakeFiles/opengl_tutorial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/opengl_tutorial.dir/Texture.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_tutorial.dir/Texture.cpp.o -MF CMakeFiles/opengl_tutorial.dir/Texture.cpp.o.d -o CMakeFiles/opengl_tutorial.dir/Texture.cpp.o -c /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Texture.cpp

CMakeFiles/opengl_tutorial.dir/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/opengl_tutorial.dir/Texture.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Texture.cpp > CMakeFiles/opengl_tutorial.dir/Texture.cpp.i

CMakeFiles/opengl_tutorial.dir/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/opengl_tutorial.dir/Texture.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/Texture.cpp -o CMakeFiles/opengl_tutorial.dir/Texture.cpp.s

# Object files for target opengl_tutorial
opengl_tutorial_OBJECTS = \
"CMakeFiles/opengl_tutorial.dir/Main.cpp.o" \
"CMakeFiles/opengl_tutorial.dir/Shader.cpp.o" \
"CMakeFiles/opengl_tutorial.dir/Texture.cpp.o"

# External object files for target opengl_tutorial
opengl_tutorial_EXTERNAL_OBJECTS =

opengl_tutorial: CMakeFiles/opengl_tutorial.dir/Main.cpp.o
opengl_tutorial: CMakeFiles/opengl_tutorial.dir/Shader.cpp.o
opengl_tutorial: CMakeFiles/opengl_tutorial.dir/Texture.cpp.o
opengl_tutorial: CMakeFiles/opengl_tutorial.dir/build.make
opengl_tutorial: /opt/homebrew/lib/libglfw.3.4.dylib
opengl_tutorial: glad/libglad.a
opengl_tutorial: stb_image/libstb_image.a
opengl_tutorial: CMakeFiles/opengl_tutorial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable opengl_tutorial"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opengl_tutorial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opengl_tutorial.dir/build: opengl_tutorial
.PHONY : CMakeFiles/opengl_tutorial.dir/build

CMakeFiles/opengl_tutorial.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opengl_tutorial.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opengl_tutorial.dir/clean

CMakeFiles/opengl_tutorial.dir/depend:
	cd /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build /Users/arthurzhao/Desktop/Code/TMFVC/OpenGL-tutorial/build/CMakeFiles/opengl_tutorial.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/opengl_tutorial.dir/depend
