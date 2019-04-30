#ifndef _SHADER_H
#define _SHADER_H

#include "shape.h"

using namespace sivelab;

class Lambertian : public shaderData
{
    public:
    // class instances
    Lambertian(){};
    ~Lambertian(){};
    Lambertian(shaderData* sdata);
    void set(shaderData* sdata);
    
    // class functions
    Vector3D apply(HitStruct hstruct);
    std::vector<shapeData*> *allShapesPtr;
    bool isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct);
};

class Blinn_phong : public shaderData
{
    public:
    // class instances
    Blinn_phong(){};
    ~Blinn_phong(){};
    Blinn_phong(shaderData* sdata);
    void set(shaderData* sdata);
    
    // class functions
    Vector3D apply(HitStruct hstruct);
    std::vector<shapeData*> *allShapesPtr;
    bool isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct);
};

class Phong : public shaderData
{
    public:
    // class instances
    Phong(){};
    ~Phong(){};
    Phong(shaderData* sdata);
    void set(shaderData* sdata);
    
    // class functions
    Vector3D apply(HitStruct hstruct);
    std::vector<shapeData*> *allShapesPtr;
    Vector3D getPhong(HitStruct hstruct, lightData ldata);
    bool isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct);
};

class Mirror : public shaderData
{
    public:
    // class instances
    float mirrorCoef;
    Mirror(){};
    ~Mirror(){};
    Mirror(shaderData* sdata);
    void set(shaderData* sdata);
    
    // class functions
    Vector3D apply(HitStruct hstruct);
    std::vector<shapeData*> *allShapesPtr;
    bool isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct);
    Vector3D getReflectObject(HitStruct hstruct);
};

class Glaze : public shaderData
{
    public:
    // class instances
    float mirrorCoef;
    Lambertian thisLambertian;
    Mirror thisMirror;
    Glaze(){};
    ~Glaze(){};
    Glaze(shaderData* sdata);
    void set(shaderData* sdata);
    
    // class functions
    Vector3D apply(HitStruct hstruct);
    std::vector<shapeData*> *allShapesPtr;
    
};

class Dielectric : public shaderData
{
    public:
    // class instances
    float mirrorCoef;
    float ar, ag, ab; //attenuation coefficients
    float refrIndex;
    float nt;

    Mirror thisMirror;
    Dielectric(){
        mirrorCoef = 1.0f;
        refrIndex =  1.333; //refractive index of water is 1.333. This will be default! try 1.01 or 0.9999
        ar = 0.4 , ag = 0.5 , ab = 0.4; // default values
    }; 
    ~Dielectric(){};
    Dielectric(shaderData* sdata);
    void set(shaderData* sdata);
    
    // class functions
    Vector3D apply(HitStruct hstruct);
    std::vector<shapeData*> *allShapesPtr;
    bool getRefractObject(Vector3D d, Vector3D n, float ref_n,  Vector3D& tRay, float nt );
    Vector3D getReflectObject(Vector3D d, Vector3D n);
    Vector3D getColor(HitStruct hstruct, Vector3D direction);
};

#endif