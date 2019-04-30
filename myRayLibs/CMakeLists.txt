cmake_minimum_required(VERSION 2.6)

# Adds the rayTracerLib directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# myRayLibs directory to correctly include the relative reference to the
# src files.
#


include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/myRayLibs)
link_directories(${CMAKE_BINARY_DIR}/myRayLibs)

add_library(raytracer-util
	camera.h ray.h light.h shader.h scene.h SceneDataTypes.h shape.h hitstruct.h shaderData.h mat4.h vec4.h
	camera.cpp ray.cpp scene.cpp shape.cpp shader.cpp hitstruct.cpp shaderData.cpp light.cpp
)

# add executable
add_executable(raytracer main.cpp
				scene.h scene.cpp
				)

# Linking CXX executable to raytracer
target_link_libraries(raytracer sive-util)
target_link_libraries(raytracer raytracer-util)
target_link_libraries(raytracer ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(raytracer ${PNG_LIBRARY})
target_link_libraries(raytracer ${ZLIB_LIBRARY})
