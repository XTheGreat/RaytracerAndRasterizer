#ifndef _SHAPE_H
#define _SHAPE_H

#include "Vector3D.h"
// Need to include the header of the code that reads and parses the
// OBJ file
#include "model_obj.h"
#include "ray.h"
#include "vec4.h"
#include "shaderData.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace sivelab;

// Shape Initialization Data

enum ShapeType {
    sphere, triangle, box
};

class shapeData
{ 
    public:
        ShapeType type;
        std::string name;
        Vector3D minPt, maxPt;
        shaderData *shader;
        float radius;
        Vector3D center, normal;
        Vector3D v0, v1, v2; 
        bool isSet;
        Vector3D shapeNormal(Vector3D ptIntersect);
        virtual bool intersect (Ray r, float tmin, float &tmax, shapeData &tshape, bool &hit) {};
        virtual Vector3D getpointIntersect(Ray r, float tmax);

        // virtual destruction function for parent class
        virtual ~shapeData() {};

        // get color based on shader type
        Vector3D getObjectColor(std::vector<lightData*> allLights, Vector3D ptIntersect);

        // OpenGL Stuff
        bool getVertexIntersections(float xaxis, float yaxis, double &alpha, double &beta, double &gamma);
};

class Triangle : public shapeData
{
    public:

    // Triangle instances
    Triangle(){}
    ~Triangle(){}
    Triangle(shapeData shape);
    Triangle(Vector3D t0, Vector3D t1, Vector3D t2);
    void set(Vector3D t0, Vector3D t1, Vector3D t2);
    bool intersect (Ray r, float tmin, float &tmax, shapeData &tshape, bool &hit);

    // OPENGL stuff
    int numFloatsNeeded;
    void initialize(std::string filename);
    float* host_VertexBuffer;
    int numBytes;
    
};

class Box : public shapeData
{
    public:
        
        std::vector<shapeData*> allTriangles;
        //Box instances
        Box(){};
        ~Box(){};
        Box(shapeData shape);
}; 

class Sphere : public shapeData
{
    public:

    // sphere instances
    Sphere(){};
    ~Sphere(){};
    Sphere(shapeData shape);
    void setParameters(shapeData shape);
    bool intersect (Ray r, float tmin, float &tmax, shapeData &tshape, bool &hit);

    // Software Rasterizeration stuff
    void rasterize();
    void tesselation(Box sphereBox);
    std::vector<shapeData*> allTriangles;
};

class Vertex
{
    public:
        float xaxis, yaxis, zCoord;
};


struct vertexData
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

#endif