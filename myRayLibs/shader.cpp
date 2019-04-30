
#include "shader.h"
// random_shuffle example
#include <algorithm>    // std::random_shuffle

// Lambertian shader
Lambertian::Lambertian(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
}

void Lambertian::set(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
}


Vector3D Lambertian::apply(HitStruct hstruct)
{
    Vector3D objectColor = this->getAmbient();
    lightData ldata, sldata;

    //std::cout << "artistic: " << artistic << std::endl;
    
    for (std::vector<lightData*>::iterator lptr = hstruct.allLights.begin(); lptr!= hstruct.allLights.end(); lptr++)
    {
        ldata = **lptr;
        std::vector<shapeData*> allShapes = *allShapesPtr;
        if(ldata.type == 0)
        {
            if(isLightVisible(allShapes, ldata, hstruct) == true)
            {
                // artistic shading!!
                if (!artistic)
                    objectColor += this->getDiffuse( hstruct, ldata);
                else
                    objectColor += this->getCellShading( hstruct, ldata);
            }
        }
        else
        {
            Vector3D thisColor;
            int i = 0;
            std::random_shuffle(ldata.areaLights.begin(), ldata.areaLights.end());
            for (std::vector<lightData*>::iterator slptr = ldata.areaLights.begin(); slptr!= ldata.areaLights.end(); slptr++)
            { if (i < hstruct.sampleRate){
                sldata = **slptr;
                if(isLightVisible(allShapes, sldata, hstruct) == true)
                {
                    if (!artistic)
                        thisColor += this->getDiffuse( hstruct, sldata);
                    else
                        thisColor += this->getCellShading( hstruct, sldata);
                }
                i++;
            }}
            thisColor = thisColor / hstruct.sampleRate;
            objectColor += thisColor;
        }
    }
    objectColor = clamp(objectColor);
    if (check)
		objectColor = this->getDiffuse( hstruct, ldata) * 0.75;
    return objectColor;
}

//visiblity test::shadows
bool Lambertian::isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct)
{
    Ray shadowRay;
    check = false;
    bool isShadow = false;
    shapeData tshape;
    float tmax, tmin;

    tmin = 0.001f;

    shadowRay.origin = hstruct.ptIntersect;
    shadowRay.direction = ldata.position - shadowRay.origin;

    tmax = sqrt(pow(shadowRay.direction[0], 2) + pow(shadowRay.direction[1], 2) + pow(shadowRay.direction[2], 2));

    shadowRay.direction.normalize(); // normalize direction

    for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
    {
        (*sptr)->intersect(shadowRay, tmin, tmax, tshape, isShadow);
        if(isShadow == true)
        {
        	if (tshape.shader->type == dielectric)
	        	check = true;
            return false;
        }
    }
    
    return true;
}



// Blinn_phong shader
Blinn_phong::Blinn_phong(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
    ks_specular = sdata->ks_specular;
    
    phongExp = sdata->phongExp;
}

void Blinn_phong::set(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
    ks_specular = sdata->ks_specular;
    phongExp = sdata->phongExp;
}

Vector3D Blinn_phong::apply(HitStruct hstruct)
{
    Vector3D objectColor = this->getAmbient();
    lightData ldata, sldata;
    for (std::vector<lightData*>::iterator lptr = hstruct.allLights.begin(); lptr!= hstruct.allLights.end(); lptr++)
    {
        ldata = **lptr;
        std::vector<shapeData*> allShapes = *allShapesPtr;
        if(ldata.type == 0)
        {
            if(isLightVisible(allShapes, ldata, hstruct) == true)
            {
                objectColor += ( this->getDiffuse( hstruct, ldata) + this->getSpecular( hstruct, ldata) );
            }
        
        }
        else
        {
            Vector3D thisColor;
            int i = 0;
            std::random_shuffle(ldata.areaLights.begin(), ldata.areaLights.end());
            
            for (std::vector<lightData*>::iterator slptr = ldata.areaLights.begin(); slptr!= ldata.areaLights.end(); slptr++)
            {
                if (i < hstruct.sampleRate){
                sldata = **slptr;
                if(isLightVisible(allShapes, sldata, hstruct) == true)
                {
                    thisColor += ( this->getDiffuse( hstruct, sldata) + this->getSpecular( hstruct, sldata) );
                }i++;
                }
            }
            thisColor = thisColor / i;
            objectColor += thisColor;
        }
        
    }
    objectColor = clamp(objectColor);
    return objectColor;
}

//visiblity test::shadows
bool Blinn_phong::isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct)
{
    Ray shadowRay;
    bool isShadow = false;
    shapeData tshape;
    float x, y, z, tmax, tmin;

    tmin = 0.001f;
    shadowRay.origin = hstruct.ptIntersect;
    shadowRay.direction = ldata.position - shadowRay.origin;
    tmax = sqrt(pow(shadowRay.direction[0], 2) + pow(shadowRay.direction[1], 2) + pow(shadowRay.direction[2], 2));
    shadowRay.direction.normalize(); // normalize direction
    
    for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
    {
        (*sptr)->intersect(shadowRay, tmin, tmax, tshape, isShadow);
        if(isShadow == true)
            return false;
    }
    return true;
}


// Phong shader
Phong::Phong(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
    ks_specular = sdata->ks_specular;
    phongExp = sdata->phongExp;
}

void Phong::set(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
    ks_specular = sdata->ks_specular;
    phongExp = sdata->phongExp;
}

Vector3D Phong::getPhong(HitStruct hstruct, lightData ldata)
{
    hstruct.viewDirection.normalize();
    Vector3D l, reflect, halfVect;
    l = ldata.position - hstruct.ptIntersect;
    l.normalize();
    reflect = (-1 * l) + (2 * (l.dot(hstruct.surfaceNormal)) * hstruct.surfaceNormal);
    hstruct.viewDirection.normalize();
    halfVect = hstruct.viewDirection + l;
    return ( kd_diffuse *  std::max(0.0, pow(hstruct.viewDirection.dot(reflect), phongExp)) );
}

Vector3D Phong::apply(HitStruct hstruct)
{
    Vector3D objectColor = this->getAmbient();
    lightData ldata, sldata;
    for (std::vector<lightData*>::iterator lptr = hstruct.allLights.begin(); lptr!= hstruct.allLights.end(); lptr++)
    {
        ldata = **lptr;
        std::vector<shapeData*> allShapes = *allShapesPtr;
        if(ldata.type == 0)
        {
            if(isLightVisible(allShapes, ldata, hstruct) == true)
            {
                objectColor += ( this->getDiffuse(hstruct, ldata) + this->getPhong(hstruct, ldata) );
            }
        }
        else
        {
            Vector3D thisColor;
            int i = 0;
            std::random_shuffle(ldata.areaLights.begin(), ldata.areaLights.end());
            
            for (std::vector<lightData*>::iterator slptr = ldata.areaLights.begin(); slptr!= ldata.areaLights.end(); slptr++)
            {
                if (i < hstruct.sampleRate){
                sldata = **slptr;
                if(isLightVisible(allShapes, sldata, hstruct) == true)
                {
                    thisColor += ( this->getDiffuse(hstruct, ldata) + this->getPhong(hstruct, ldata) );
                }i++;
                }
            }
            thisColor = thisColor / hstruct.sampleRate;
            objectColor += thisColor;
        }
        
    }
    objectColor = clamp(objectColor);
    return objectColor;
}

//visiblity test::shadows
bool Phong::isLightVisible(std::vector<shapeData*> allShapes, lightData ldata, HitStruct hstruct)
{
    Ray shadowRay;
    bool isShadow = false;
    shapeData tshape;
    float x, y, z, tmax, tmin;

    tmin = 0.001f;
    shadowRay.origin = hstruct.ptIntersect;
    shadowRay.direction = ldata.position - shadowRay.origin;
    tmax = sqrt(pow(shadowRay.direction[0], 2) + pow(shadowRay.direction[1], 2) + pow(shadowRay.direction[2], 2));
    shadowRay.direction.normalize(); // normalize direction
    
    for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
    {
        (*sptr)->intersect(shadowRay, tmin, tmax, tshape, isShadow);
        if(isShadow == true)
            return false;
    }
    return true;
}

// Mirror shader
Mirror::Mirror(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
}

void Mirror::set(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
}

Vector3D Mirror::apply(HitStruct hstruct)
{
    Vector3D objectColor;
    if (*depthPtr > 0)
        objectColor = getReflectObject(hstruct) * mirrorCoef;
    return (objectColor);
}

Vector3D Mirror::getReflectObject(HitStruct hstruct)
{
    Ray reflectionRay;
    shapeData tshape;
    Vector3D reflection, ptIntersect;
    float tmin = 0.001f, tmax;
    bool hit = false;
    HitStruct this_hstruct;

    reflection = hstruct.rayDirection - 2 * (hstruct.rayDirection.dot(hstruct.surfaceNormal)) * hstruct.surfaceNormal;
    reflectionRay.origin = hstruct.ptIntersect;
    reflectionRay.direction = reflection;
    tmax = INFINITY;

    std::vector<shapeData*> allShapes = *allShapesPtr;
    for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
    {
        (*sptr)->intersect(reflectionRay, tmin, tmax, tshape, hit);
    }
    if(hit == true)
    {
        *depthPtr = (*depthPtr) - 1;
        ptIntersect = tshape.getpointIntersect(reflectionRay, tmax);
        this_hstruct.set( hstruct.allLights, reflectionRay.direction, (reflectionRay.origin - ptIntersect), ptIntersect, tshape.shapeNormal(ptIntersect), tmin, tmax);
        return (tshape.shader)->apply(this_hstruct);
    }
}

// Glaze shader
Glaze::Glaze(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
}

void Glaze::set(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    kd_diffuse = sdata->kd_diffuse;
}

Vector3D Glaze::apply(HitStruct hstruct)
{
    Vector3D objectColor;
    objectColor.set(0.0f, 0.0f, 0.0f);
    
    // Create a lambertian shader
    thisLambertian.set(this);
    thisLambertian.allShapesPtr = allShapesPtr;
    objectColor = objectColor + thisLambertian.apply(hstruct);

    // Create a mirror shader
    thisMirror.set(this);
    thisMirror.mirrorCoef = mirrorCoef;
    thisMirror.depthPtr = depthPtr;
    thisMirror.allShapesPtr = allShapesPtr;
    objectColor = objectColor + thisMirror.apply(hstruct);
   
    objectColor = clamp(objectColor);
    return objectColor;
}


// Dielectric shader
Dielectric::Dielectric(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    mirrorCoef = 1.0f;
}

void Dielectric::set(shaderData* sdata)
{
    type = sdata->type;
    name = sdata->name;
    artistic = sdata->artistic;
    mirrorCoef = 1.0f;
}

Vector3D Dielectric::apply(HitStruct hstruct)
{
    Vector3D k, objectColor, reflect, transmitVector;
    Vector3D pr, pt;
    float kr, kg, kb; // coefficient of RGB
    double c, dn, t = hstruct.tmax;
    
    Vector3D lhs, rhs;
    double tmp, R0, R;
    
    reflect = getReflectObject(hstruct.rayDirection, hstruct.surfaceNormal);

    hstruct.rayDirection.normalize();
    dn = hstruct.rayDirection.dot(hstruct.surfaceNormal);
    
    if (dn < 0) // entering the dielectric
    {
        // refract(d, n, n, t)
        nt = 1.0;
        getRefractObject(hstruct.rayDirection, hstruct.surfaceNormal, refrIndex, transmitVector, nt);
        c = -1 * dn;
        kr = 1; kg = 1; kb = 1;
        k.set(kr, kg, kb);
    }
    else // leaving the dielectric
    {
        kr = exp(-1 * ar * 1);
        kg = exp(-1 * ag * 1);
        kb = exp(-1 * ab * 1);
        k.set(kr, kg, kb);
        nt = refrIndex;
        // if refract(d, −n, 1/n, t) then <should this be bool?>
        if (getRefractObject(hstruct.rayDirection, (-1 * hstruct.surfaceNormal) , ( 1 / refrIndex), transmitVector, nt) )
        {
            c = transmitVector.dot(hstruct.surfaceNormal);
        }
        else
        {
        	// return k ∗ color(p + tr)
        	pr = hstruct.ptIntersect + (t * reflect);
        	objectColor = 1 * ( getColor( hstruct, pr ) );
            return objectColor;
        }
    }

    R0 = pow((refrIndex - 1) , 2) / pow((refrIndex + 1) , 2);
    R = R0 + ( (1 - R0) * pow((1 - c), 5) );
    pr = hstruct.ptIntersect + (t * reflect);
    pt =  hstruct.ptIntersect + (t * transmitVector);
    // return k(R color(p + tr) + (1 − R) color(p + tt))
    objectColor = 1 * ( (R * getColor( hstruct, pr ) ) + ((1 - R) * getColor( hstruct, pt ) ) );
    return objectColor;
}

//getColor of Refraacted Ray
Vector3D Dielectric::getColor(HitStruct hstruct, Vector3D direction)
{
	Vector3D color, ptIntersect;
    Ray  refRay;
    shapeData tshape;
    HitStruct this_hstruct;
    float x, y, z, tmax, tmin;
    bool hit = false;
    refRay.origin = hstruct.ptIntersect;
    refRay.direction = direction - refRay.origin;

    tmin = 1.0f;
    tmax = sqrt(pow(refRay.direction[0], 2) + pow(refRay.direction[1], 2) + pow(refRay.direction[2], 2));
    refRay.direction.normalize(); // normalize direction

    std::vector<shapeData*> allShapes = *allShapesPtr;
    for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
    {
        (*sptr)->intersect(refRay, tmin, tmax, tshape, hit);
        if(hit == true)
        {
			ptIntersect = tshape.getpointIntersect(refRay, tmax);
			this_hstruct.set( hstruct.allLights, refRay.direction, (refRay.origin - ptIntersect), ptIntersect, tshape.shapeNormal(ptIntersect), tmin, tmax);
			color = (tshape.shader)->apply(this_hstruct);
        }
        
    }
    return color;
}

bool Dielectric::getRefractObject(Vector3D d, Vector3D n, float ref_n, Vector3D& transmitVector, float nt )
{
    Vector3D lhs, rhs;
    double tmp;
    double dn = d.dot(n);
    

    lhs = (ref_n * (d - (n * dn ))) / nt;
    tmp = 1 - ((pow(refrIndex, 2) * (1 - pow(dn, 2))) / pow(nt, 2));
    rhs = n * sqrt(tmp);

    transmitVector = lhs - rhs;

    if (tmp < 0.0f)
        return false;
    else
        return true;
}

Vector3D Dielectric::getReflectObject(Vector3D d, Vector3D n)
{
    Vector3D r;
    r = d - (2 * (d.dot(n)) * n);
    return r;
}