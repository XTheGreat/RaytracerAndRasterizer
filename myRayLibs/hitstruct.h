#ifndef _HITSTRUCT_H
#define _HITSTRUCT_H

#include "Vector3D.h"
#include "light.h"

using namespace sivelab;

struct HitStruct
{
    std::vector<lightData*> allLights;
    Vector3D viewDirection, ptIntersect, surfaceNormal, rayDirection;
    float tmin, tmax;
    int sampleRate; // how many random samples to select from area light
    void set(std::vector<lightData*> allLightDatas, Vector3D rDirection, Vector3D viewD, Vector3D ptI, Vector3D surfNorm, float tminimum, float tmaximum);
};

#endif