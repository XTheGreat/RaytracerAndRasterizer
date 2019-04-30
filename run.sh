#!/bin/bash
# This file runs the raytracer executables with the scene XML files.
clear
echo "The script starts now."
echo "Rendering files..."
sleep 5
for f in sceneXMLs/scenes_A/*.xml; do ./myRayLibs/raytracer -i $f -w 400 -h 400 -o sceneOutputs/$f; done
sleep 5
echo "All files have been rendered. They are available in the folder sceneXMLs/scenes_A"
