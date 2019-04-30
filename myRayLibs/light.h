#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vector3D.h"

using namespace sivelab;

// Light Initialization Data

enum LightType {
    point, area
};

struct lightData 
{
    LightType type;
    Vector3D position;
    Vector3D intensity;
    Vector3D normal;
    float width, length;
    int randomrate;

    // Sampling area light
    std::vector<lightData*> areaLights;
    
    lightData(){};
    ~lightData(){};

    void setDefault();
    void lightSampling();
};

#endif