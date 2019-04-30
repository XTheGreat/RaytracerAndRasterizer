CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (OpenGL_FCG)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

# --------------------------------------------------------------------
# PNG and ZLIB
# 
# This macro will attempt to locate the PNG include directories, link
# directories and libraries. The INCLUDE_DIRECTORIES macro adds the
# resulting include directories to the search path.
# --------------------------------------------------------------------
find_package(PNG REQUIRED)
if (PNG_FOUND)
  INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})
else (PNG_FOUND)
  MESSAGE(STATUS "Could not find the PNG Libraries!")
endif (PNG_FOUND)

# --------------------------------------------------------------------
# OpenGL Related Components
# --------------------------------------------------------------------
# Not currently using GLEW
# FIND_PACKAGE(GLEW REQUIRED)
# INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})

FIND_PACKAGE(OpenGL REQUIRED)

# To be able to include the GLFW header from your code, you need to
# tell the compiler where to find it.
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw-master)

# Once GLFW has been added to the project, the GLFW_LIBRARIES cache
# variable contains all link-time dependencies of GLFW as it is
# currently configured. To link against GLFW, link against them and
# the glfw target.
include_directories(${CMAKE_SOURCE_DIR}/glfw-master/include)
MESSAGE(STATUS "${GLFW_LIBRARIES}")
SET(GLFW_STATIC_LIBRARIES "${GLFW_LIBRARIES}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/glm-0.9.8.5)

# ----------------------------------------------------------
# Boost
#
# This section tests for Boost support on the system. Boost is
# required as it is used heavily with this code. Boost also allows the
# code to be nicely portable across Operating Systems.
# ----------------------------------------------------------
# SET (Boost_MULTITHREADED TRUE)

# If you want to get more info on what the Find Boost macro is
# doing...  
# SET(Boost_DEBUG 1)

# Necessary to get Win32 version to work, plus, not a bad idea to link
# statically for our purposes.
SET(Boost_USE_STATIC_LIBS TRUE)

#FIND_PACKAGE(Boost REQUIRED date_time program_options system thread unit_test_framework chrono timer)
FIND_PACKAGE(Boost REQUIRED COMPONENTS date_time program_options system timer)
IF(${Boost_FOUND})
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  MESSAGE(STATUS "Boost Libs: ${Boost_LIBRARIES}")
ENDIF()

# Add the src directory to build the util library.
add_subdirectory(src)

# If you want, we can also compile the tests directory that are
# essentially examples for how to use some of the classes and code.
add_subdirectory(examples)

#
# OpenGL Example
#
# This builds a simple OpenGL example that you can use to get started with OpenGL.
#
add_subdirectory(OpenGL)

#
# Raytracer Directory
#
# This builds and renders a scene using ray tracing.
#
add_subdirectory(myRayLibs)

#
# Hardware Rasterizer Directory
#
# This builds and renders a scene with opengl hardware functionalities.
#
add_subdirectory(HwRasterize)

#
# Unit Tests - by enabling testing with cmake, we can create a target
# that lets unit tests be run. After re-building yourproject with
# ENABLE_TESTING called, a make target, called test will be
# enabled. You can then type
# 
#  make test
#
# to perform the unit tests. See the CMakeLists.txt file in the utests
# directory for more details. Also, see the unit test .cpp files in
# the utests directory for examples on using Boost's unit test system.
#
ENABLE_TESTING()
add_subdirectory(utests)
