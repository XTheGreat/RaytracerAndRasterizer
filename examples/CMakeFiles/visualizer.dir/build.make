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
include examples/CMakeFiles/visualizer.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/visualizer.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/visualizer.dir/flags.make

examples/CMakeFiles/visualizer.dir/visualize.cpp.o: examples/CMakeFiles/visualizer.dir/flags.make
examples/CMakeFiles/visualizer.dir/visualize.cpp.o: examples/visualize.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/visualizer.dir/visualize.cpp.o"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/examples" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/visualizer.dir/visualize.cpp.o -c "/home/adigu002/Documents/CS 5721/myRayTracer/examples/visualize.cpp"

examples/CMakeFiles/visualizer.dir/visualize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualizer.dir/visualize.cpp.i"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/examples" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/adigu002/Documents/CS 5721/myRayTracer/examples/visualize.cpp" > CMakeFiles/visualizer.dir/visualize.cpp.i

examples/CMakeFiles/visualizer.dir/visualize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualizer.dir/visualize.cpp.s"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/examples" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/adigu002/Documents/CS 5721/myRayTracer/examples/visualize.cpp" -o CMakeFiles/visualizer.dir/visualize.cpp.s

examples/CMakeFiles/visualizer.dir/visualize.cpp.o.requires:

.PHONY : examples/CMakeFiles/visualizer.dir/visualize.cpp.o.requires

examples/CMakeFiles/visualizer.dir/visualize.cpp.o.provides: examples/CMakeFiles/visualizer.dir/visualize.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/visualizer.dir/build.make examples/CMakeFiles/visualizer.dir/visualize.cpp.o.provides.build
.PHONY : examples/CMakeFiles/visualizer.dir/visualize.cpp.o.provides

examples/CMakeFiles/visualizer.dir/visualize.cpp.o.provides.build: examples/CMakeFiles/visualizer.dir/visualize.cpp.o


# Object files for target visualizer
visualizer_OBJECTS = \
"CMakeFiles/visualizer.dir/visualize.cpp.o"

# External object files for target visualizer
visualizer_EXTERNAL_OBJECTS =

examples/visualizer: examples/CMakeFiles/visualizer.dir/visualize.cpp.o
examples/visualizer: examples/CMakeFiles/visualizer.dir/build.make
examples/visualizer: src/libsive-util.a
examples/visualizer: /usr/lib/x86_64-linux-gnu/libboost_program_options.a
examples/visualizer: /usr/lib/x86_64-linux-gnu/libpng.so
examples/visualizer: /usr/lib/x86_64-linux-gnu/libz.so
examples/visualizer: examples/CMakeFiles/visualizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable visualizer"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/visualizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/visualizer.dir/build: examples/visualizer

.PHONY : examples/CMakeFiles/visualizer.dir/build

examples/CMakeFiles/visualizer.dir/requires: examples/CMakeFiles/visualizer.dir/visualize.cpp.o.requires

.PHONY : examples/CMakeFiles/visualizer.dir/requires

examples/CMakeFiles/visualizer.dir/clean:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/examples" && $(CMAKE_COMMAND) -P CMakeFiles/visualizer.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/visualizer.dir/clean

examples/CMakeFiles/visualizer.dir/depend:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/examples" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/examples" "/home/adigu002/Documents/CS 5721/myRayTracer/examples/CMakeFiles/visualizer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : examples/CMakeFiles/visualizer.dir/depend

