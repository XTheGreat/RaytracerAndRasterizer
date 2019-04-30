cmake_minimum_required(VERSION 2.6)

# Adds the src directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# src directory to correctly include the relative reference to the
# src files.
#

include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR}/src)

add_library (sive-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  model_obj.cpp model_obj.h
  Random.cpp Random.h
  SceneDataContainer.h
  Timer.cpp Timer.h
  Vector3D.h Vector3D.cpp
  XMLSceneParser.h XMLSceneParser.cpp
)

