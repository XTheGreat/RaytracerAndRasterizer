cmake_minimum_required(VERSION 2.6)

# Adds the rasterizerLib directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# myRayLibs directory to correctly include the relative reference to the
# src files.
#

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()


INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries (${OPENGL_LIBRARY})
include_directories(${CMAKE_SOURCE_DIR}/myRayLibs)
link_directories(${CMAKE_BINARY_DIR}/myRayLibs)
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/HwRasterize)
link_directories(${CMAKE_BINARY_DIR}/HwRasterize)

# adding library
add_library(HwRasterizer-util
    main.cpp
)

# add executable
add_executable(Hrasterizer main.cpp
		GLSLObject.h GLSLObject.cpp
)

# Linking CXX executable to rasterizer
target_link_libraries (Hrasterizer raytracer-util)
target_link_libraries (Hrasterizer sive-util)
target_link_libraries (Hrasterizer HwRasterizer-util)
target_link_libraries (Hrasterizer ${Boost_LIBRARIES})
target_link_libraries (Hrasterizer glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries (Hrasterizer glfw ${GDAL_LIBRARY})
target_link_libraries (Hrasterizer ${GLEW})
target_link_libraries (Hrasterizer ${PNG_LIBRARIES})
target_link_libraries (Hrasterizer ${ZLIB_LIBRARIES})
