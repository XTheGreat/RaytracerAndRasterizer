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
include rasterizerLibs/CMakeFiles/rasterizer-util.dir/depend.make

# Include the progress variables for this target.
include rasterizerLibs/CMakeFiles/rasterizer-util.dir/progress.make

# Include the compile flags for this target's objects.
include rasterizerLibs/CMakeFiles/rasterizer-util.dir/flags.make

rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o: rasterizerLibs/CMakeFiles/rasterizer-util.dir/flags.make
rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o: rasterizerLibs/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rasterizer-util.dir/main.cpp.o -c "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs/main.cpp"

rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rasterizer-util.dir/main.cpp.i"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs/main.cpp" > CMakeFiles/rasterizer-util.dir/main.cpp.i

rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rasterizer-util.dir/main.cpp.s"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs/main.cpp" -o CMakeFiles/rasterizer-util.dir/main.cpp.s

rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.requires:

.PHONY : rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.requires

rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.provides: rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.requires
	$(MAKE) -f rasterizerLibs/CMakeFiles/rasterizer-util.dir/build.make rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.provides.build
.PHONY : rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.provides

rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.provides.build: rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o


# Object files for target rasterizer-util
rasterizer__util_OBJECTS = \
"CMakeFiles/rasterizer-util.dir/main.cpp.o"

# External object files for target rasterizer-util
rasterizer__util_EXTERNAL_OBJECTS =

rasterizerLibs/librasterizer-util.a: rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o
rasterizerLibs/librasterizer-util.a: rasterizerLibs/CMakeFiles/rasterizer-util.dir/build.make
rasterizerLibs/librasterizer-util.a: rasterizerLibs/CMakeFiles/rasterizer-util.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/adigu002/Documents/CS 5721/myRayTracer/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librasterizer-util.a"
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" && $(CMAKE_COMMAND) -P CMakeFiles/rasterizer-util.dir/cmake_clean_target.cmake
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rasterizer-util.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rasterizerLibs/CMakeFiles/rasterizer-util.dir/build: rasterizerLibs/librasterizer-util.a

.PHONY : rasterizerLibs/CMakeFiles/rasterizer-util.dir/build

rasterizerLibs/CMakeFiles/rasterizer-util.dir/requires: rasterizerLibs/CMakeFiles/rasterizer-util.dir/main.cpp.o.requires

.PHONY : rasterizerLibs/CMakeFiles/rasterizer-util.dir/requires

rasterizerLibs/CMakeFiles/rasterizer-util.dir/clean:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" && $(CMAKE_COMMAND) -P CMakeFiles/rasterizer-util.dir/cmake_clean.cmake
.PHONY : rasterizerLibs/CMakeFiles/rasterizer-util.dir/clean

rasterizerLibs/CMakeFiles/rasterizer-util.dir/depend:
	cd "/home/adigu002/Documents/CS 5721/myRayTracer" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" "/home/adigu002/Documents/CS 5721/myRayTracer" "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs" "/home/adigu002/Documents/CS 5721/myRayTracer/rasterizerLibs/CMakeFiles/rasterizer-util.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : rasterizerLibs/CMakeFiles/rasterizer-util.dir/depend

