# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/adigu002/Documents/CS 5721/myRayTracer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/adigu002/Documents/CS 5721/myRayTracer"

# Include any dependencies generated for this target.
include OpenGL/CMakeFiles/glfwExample.dir/depend.make

# Include the progress variables for this target.
include OpenGL/CMakeFiles/glfwExample.dir/progress.make

# Include the compile flags for this target's objects.
include OpenGL/CMakeFiles/glfwExample.dir/flags.make

OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o: OpenGL/CMakeFiles/glfwExample.dir/flags.make
OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o: OpenGL/glfwExample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glfwExample.dir/glfwExample.cpp.o -c "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL/glfwExample.cpp"

OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glfwExample.dir/glfwExample.cpp.i"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL/glfwExample.cpp" > CMakeFiles/glfwExample.dir/glfwExample.cpp.i

OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glfwExample.dir/glfwExample.cpp.s"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL/glfwExample.cpp" -o CMakeFiles/glfwExample.dir/glfwExample.cpp.s

OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.requires:

.PHONY : OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.requires

OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.provides: OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.requires
	$(MAKE) -f OpenGL/CMakeFiles/glfwExample.dir/build.make OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.provides.build
.PHONY : OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.provides

OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.provides.build: OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o


# Object files for target glfwExample
glfwExample_OBJECTS = \
"CMakeFiles/glfwExample.dir/glfwExample.cpp.o"

# External object files for target glfwExample
glfwExample_EXTERNAL_OBJECTS =

OpenGL/glfwExample: OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o
OpenGL/glfwExample: OpenGL/CMakeFiles/glfwExample.dir/build.make
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libGLU.so
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libGL.so
OpenGL/glfwExample: glfw-master/src/libglfw3.a
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libpng.so
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libz.so
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libz.so
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/librt.so
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libm.so
OpenGL/glfwExample: /usr/lib/x86_64-linux-gnu/libX11.so
OpenGL/glfwExample: OpenGL/CMakeFiles/glfwExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable glfwExample"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glfwExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
OpenGL/CMakeFiles/glfwExample.dir/build: OpenGL/glfwExample

.PHONY : OpenGL/CMakeFiles/glfwExample.dir/build

OpenGL/CMakeFiles/glfwExample.dir/requires: OpenGL/CMakeFiles/glfwExample.dir/glfwExample.cpp.o.requires

.PHONY : OpenGL/CMakeFiles/glfwExample.dir/requires

OpenGL/CMakeFiles/glfwExample.dir/clean:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" && $(CMAKE_COMMAND) -P CMakeFiles/glfwExample.dir/cmake_clean.cmake
.PHONY : OpenGL/CMakeFiles/glfwExample.dir/clean

OpenGL/CMakeFiles/glfwExample.dir/depend:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL" "/home/adigu002/Documents/CS 5721/myRayTracer/OpenGL/CMakeFiles/glfwExample.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : OpenGL/CMakeFiles/glfwExample.dir/depend

