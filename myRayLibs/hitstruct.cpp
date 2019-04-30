#include "hitstruct.h"

void HitStruct::set(std::vector<lightData*> allLightDatas, Vector3D rDirection, Vector3D viewD, Vector3D ptI, Vector3D surfNorm, float tminimum, float tmaximum)
{
    allLights = allLightDatas;
    viewDirection = viewD;
    ptIntersect = ptI;
    surfaceNormal = surfNorm;
    tmin = tminimum;
    tmax = tmaximum;
    rayDirection = rDirection;
}

