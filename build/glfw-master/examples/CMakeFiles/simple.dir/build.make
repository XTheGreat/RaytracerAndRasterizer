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
CMAKE_BINARY_DIR = "/home/adigu002/Documents/CS 5721/myRayTracer/build"

# Include any dependencies generated for this target.
include glfw-master/examples/CMakeFiles/simple.dir/depend.make

# Include the progress variables for this target.
include glfw-master/examples/CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include glfw-master/examples/CMakeFiles/simple.dir/flags.make

glfw-master/examples/CMakeFiles/simple.dir/simple.c.o: glfw-master/examples/CMakeFiles/simple.dir/flags.make
glfw-master/examples/CMakeFiles/simple.dir/simple.c.o: ../glfw-master/examples/simple.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw-master/examples/CMakeFiles/simple.dir/simple.c.o"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/simple.dir/simple.c.o   -c "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/examples/simple.c"

glfw-master/examples/CMakeFiles/simple.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/simple.c.i"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/examples/simple.c" > CMakeFiles/simple.dir/simple.c.i

glfw-master/examples/CMakeFiles/simple.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/simple.c.s"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/examples/simple.c" -o CMakeFiles/simple.dir/simple.c.s

glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.requires:

.PHONY : glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.requires

glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.provides: glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.requires
	$(MAKE) -f glfw-master/examples/CMakeFiles/simple.dir/build.make glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.provides.build
.PHONY : glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.provides

glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.provides.build: glfw-master/examples/CMakeFiles/simple.dir/simple.c.o


glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o: glfw-master/examples/CMakeFiles/simple.dir/flags.make
glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o: ../glfw-master/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/simple.dir/__/deps/glad.c.o   -c "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/deps/glad.c"

glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/__/deps/glad.c.i"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/deps/glad.c" > CMakeFiles/simple.dir/__/deps/glad.c.i

glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/__/deps/glad.c.s"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/deps/glad.c" -o CMakeFiles/simple.dir/__/deps/glad.c.s

glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.requires:

.PHONY : glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.requires

glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.provides: glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.requires
	$(MAKE) -f glfw-master/examples/CMakeFiles/simple.dir/build.make glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.provides.build
.PHONY : glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.provides

glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.provides.build: glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o


# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/simple.c.o" \
"CMakeFiles/simple.dir/__/deps/glad.c.o"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

glfw-master/examples/simple: glfw-master/examples/CMakeFiles/simple.dir/simple.c.o
glfw-master/examples/simple: glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o
glfw-master/examples/simple: glfw-master/examples/CMakeFiles/simple.dir/build.make
glfw-master/examples/simple: glfw-master/src/libglfw3.a
glfw-master/examples/simple: /usr/lib/x86_64-linux-gnu/libm.so
glfw-master/examples/simple: /usr/lib/x86_64-linux-gnu/librt.so
glfw-master/examples/simple: /usr/lib/x86_64-linux-gnu/libm.so
glfw-master/examples/simple: /usr/lib/x86_64-linux-gnu/libX11.so
glfw-master/examples/simple: glfw-master/examples/CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable simple"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw-master/examples/CMakeFiles/simple.dir/build: glfw-master/examples/simple

.PHONY : glfw-master/examples/CMakeFiles/simple.dir/build

glfw-master/examples/CMakeFiles/simple.dir/requires: glfw-master/examples/CMakeFiles/simple.dir/simple.c.o.requires
glfw-master/examples/CMakeFiles/simple.dir/requires: glfw-master/examples/CMakeFiles/simple.dir/__/deps/glad.c.o.requires

.PHONY : glfw-master/examples/CMakeFiles/simple.dir/requires

glfw-master/examples/CMakeFiles/simple.dir/clean:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" && $(CMAKE_COMMAND) -P CMakeFiles/simple.dir/cmake_clean.cmake
.PHONY : glfw-master/examples/CMakeFiles/simple.dir/clean

glfw-master/examples/CMakeFiles/simple.dir/depend:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/glfw-master/examples" "/home/adigu002/Documents/CS 5721/myRayTracer/build" "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples" "/home/adigu002/Documents/CS 5721/myRayTracer/build/glfw-master/examples/CMakeFiles/simple.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : glfw-master/examples/CMakeFiles/simple.dir/depend

