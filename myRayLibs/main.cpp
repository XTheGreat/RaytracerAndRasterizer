/*
 *  main.cpp
 *
 *  Created by Christianah Adigun
 *  Copyright 2018. All rights reserved.
 *
 * This file is part of CS5721 Computer Graphics library (cs5721Graphics).
 * 
 * Implementation of the raytracing algorithm.
 *
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include "scene.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  XMLSceneParser xmlScene;

  Scene *sceneFactory = new Scene();

  // register object creation function with xmlScene
  xmlScene.registerCallback("camera", sceneFactory);
  xmlScene.registerCallback("light", sceneFactory);
  xmlScene.registerCallback("shader", sceneFactory);
  xmlScene.registerCallback("shape", sceneFactory);



  if (args.inputFileName != "")
  {
    // Raytrace this file
    // reading xml files
    sceneFactory->depthOfFieldDistance = args.depthOfFieldDistance;
    sceneFactory->recursionDepth = args.recursionDepth;
    sceneFactory->rpp = args.rpp;
    sceneFactory->sampleRate = args.sampleRate;
    sceneFactory->artistic = args.artistic;
    
    if(args.inputFileName.substr(args.inputFileName.find_last_of(".") + 1) == "obj") 
    {
      // Reading obj files
      sceneFactory->readObjFile(args.inputFileName);
      sceneFactory->raytraceRenderer( args.inputFileName, args.width, args.height );
    }
    else if(args.inputFileName.substr(args.inputFileName.find_last_of(".") + 1) == "xml") 
    {
      sceneFactory->rasterize = args.rasterize;
      xmlScene.parseFile( args.inputFileName );
      if (!args.rasterize)
      {
        std::cout << "artistic: " << sceneFactory->artistic << std::endl;
        sceneFactory->raytraceRenderer( args.inputFileName, args.width, args.height );
      }
      else
        sceneFactory->rasterizeRenderer( args.inputFileName, args.width, args.height );
    }
    else
    {
      std::cout << "Invalid file type provided!" << std::endl;
    }
  }
  else
    {
      std::cerr << "Need input file!" << std::endl;
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}


