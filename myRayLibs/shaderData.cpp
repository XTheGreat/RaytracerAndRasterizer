#include "shaderData.h"

// general shader class base class functions

Vector3D shaderData::clamp(Vector3D vectorObject)
{
    for (size_t i = 0; i<3; i++)
    {
        if(vectorObject[i] > 1.0)
            vectorObject[i] = 1.0f;
        if(vectorObject[i] < 0.0)
            vectorObject[i] = 0.0f;
    }
    return vectorObject;
}


//Diffuse, Ambient & Specular components
Vector3D shaderData::getDiffuse(HitStruct hstruct, lightData ldata)
{
    Vector3D l = ldata.position - hstruct.ptIntersect;
    l.normalize();
    return (kd_diffuse * ldata.intensity * std::max(0.0, hstruct.surfaceNormal.dot(l)));
};

Vector3D shaderData::getAmbient()
{
    return (kd_diffuse * 0.1);
};

Vector3D shaderData::getSpecular(HitStruct hstruct, lightData ldata)
{
    Vector3D l = ldata.position - hstruct.ptIntersect;
    l.normalize();
    hstruct.viewDirection.normalize();
    Vector3D halfVect =  l + hstruct.viewDirection;
    halfVect.normalize();
    return (ks_specular * ldata.intensity *  std::max(0.0, pow(hstruct.surfaceNormal.dot(halfVect), phongExp)) );
};

int shaderData::getShadingRatio(Vector3D objectColor)
{
    int percent;
    float diffCoef, objCoef;
    diffCoef = kd_diffuse[0] + kd_diffuse[1] + kd_diffuse[2];
    objCoef = objectColor[0] + objectColor[1] + objectColor[2];
    return ((diffCoef - objCoef) / diffCoef);

}

Vector3D shaderData::getCellShading(HitStruct hstruct, lightData ldata)
{
    Vector3D objectColor;
    float kw;
    kc_color.set(0.4, 0.4, 0.7);
    Vector3D l = ldata.position - hstruct.ptIntersect;
    l.normalize();
    kw = (1 + std::max(0.0, hstruct.surfaceNormal.dot(l)) ) / 2.0f;
    kd_diffuse.set( 1.0, 0.4, 0.4);

    objectColor = (kw * getDiffuse(hstruct, ldata)) + ( (1 - kw) * kc_color );
    return objectColor;
}