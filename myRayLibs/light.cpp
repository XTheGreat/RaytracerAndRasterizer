#include "light.h"
#include "cstdlib"


void lightData::setDefault()
{
    type = point;
    position.set(0, 10, 0);
    intensity.set(1.0f, 1.0f, 1.0f);
};

void lightData::lightSampling()
{
    int randomrate = 10;

    lightData sampleLight;
    float halfWidth, halfLength, epislom, diffx, diffy;
    float min, xmin, ymin, u, v, w;

    diffx = width / randomrate;
    diffy = length /randomrate;

    halfWidth = width / 2;
    halfLength = length / 2;

    min = position[0] - halfWidth;
    ymin = position[2] - halfLength;
    
    v = position[1];

    Vector3D thisPosition, l;
    
    srand(time(0));

    for (int p = 0; p <randomrate; p++)
    {
        xmin = min;
        for (int q = 0; q <randomrate; q++)
        {
            epislom = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1));
            u = xmin + (diffx * epislom);
            w = ymin + (diffy * epislom);
            thisPosition.set(u, v, w);
            sampleLight.position = thisPosition;
            sampleLight.intensity = intensity;
            areaLights.push_back(new lightData(sampleLight));
            xmin += diffx;            
        }
        ymin += diffy;
    }
    
}