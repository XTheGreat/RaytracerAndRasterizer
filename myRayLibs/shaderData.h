#ifndef _SHADERDATA_H
#define _SHADERDATA_H

#include "hitstruct.h"

using namespace sivelab;


enum ShaderType {
    lambertian, blinnphong, phong, mirror, glaze, dielectric
};

struct shaderData 
{
    public:
    // properties
    ShaderType type;
    bool artistic;
    bool check;
    std::string name;
    Vector3D kd_diffuse, ks_specular, kc_color;
    float phongExp;
    int *depthPtr; // useful for mirror object depth recursion

    // functions
    Vector3D clamp(Vector3D vectorObject);
    virtual Vector3D apply(HitStruct hstruct) {};
    
    //gets Diffuse, Ambient & Specular components
    Vector3D getDiffuse(HitStruct hstruct, lightData ldata);
    Vector3D getAmbient();
    Vector3D getSpecular(HitStruct hstruct, lightData ldata);
    Vector3D getCellShading(HitStruct hstruct, lightData ldata);
    int getShadingRatio(Vector3D objectColor);

    // conduct a visiblility test for shadow ray
    bool IsVisible();

    //OPENGL Stuff
    virtual Vector3D fragmentShader(HitStruct hstruct) {};

};


#endif