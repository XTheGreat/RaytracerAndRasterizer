#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <map>

#include "Vector3D.h"
#include "handleGraphicsArgs.h"
#include "XMLSceneParser.h"
#include "SceneDataTypes.h"
#include "png++/png.hpp"

using namespace sivelab;

//
// Scene Parameters
//

class Scene : public sivelab::SceneElementCreator  {

    private:
    std::vector<cameraData*> allCameras;
    
    // std::vector<shapeData*> allShapes;
    // std::vector<lightData*> allLights;
    
    public:
    std::vector<shapeData*> allShapes;
    std::vector<lightData*> allLights;
    // Make camera global for now!
    cameraData cam;
    
    struct sceneParamData 
    {
        Vector3D backgroundColor;
        bool usesEnvMap;
        std::string envMapPrefix;
    };

    Scene() {}
    ~Scene() {}
    // read file name
    void readSceneFile( std::string &filename );
    //read obj file
    void readObjFile( std::string filename );
    // create scene instance
    void instance( ptree::value_type const &v );
    // ray trace the scene
    void raytraceRenderer( std::string filename, int nX, int nY );

    // some scene container params
    float depthOfFieldDistance;
    int recursionDepth, tempDepth, rpp, sampleRate;
    bool artistic; // turn on artistic shading

    /*pointers to general 
    things, such as Cameras, Shapes 
    and Shaders */
    
    shapeData myShape;
    /*** Setters for the objects ***/
    void addShape( shapeData* shape );
    void addShape( std::vector<Triangle*> listOfTriangles );
    void addLight( lightData* light );
    /*** Setters for the objects ***/

    //compute color of nearest object hit.
    void getHitStructure(Ray r, float tmin, float &tmax, shapeData& tshape, bool &hit);
    void depthOfFieldRendering ( std::string filename, int nX, int nY , float depthBuffer[] ){};
    Vector3D depthColor (cameraData *this_CamPtr, HitStruct hstruct, Ray r, float left, float right, int j, int i, int nX, int nY, float &distance);
    
    // parse shape data
    void parseShapeData( ptree::value_type const &v );
    // parse shader data
    shaderData* parseShaderData( ptree::value_type const &v );
    //shaderMap
    std::map<std::string, shaderData*> shaderMap;
    // check if light is visible
    bool isLightVisible(Ray shadowRay, float tmin, float &tmax);


    /*****
    SOFTWARE RASTERIZER STUFF
    ******/
   bool rasterize;
   void computeMinMax(std::vector<Vec4*> vertexBufferObject, double &x_min, double &x_max, double &y_min, double &y_max);
   void rasterizeRenderer( std::string filename, int nX, int nY );


};

#endif