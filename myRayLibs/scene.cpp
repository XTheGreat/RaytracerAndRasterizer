// Scene class’s member gets called here.

#include "scene.h"

using namespace sivelab;

void Scene::readSceneFile( std::string &filename ) { 
  XMLSceneParser xmlScene;
  // Right now, your code only supports cameras 
  // and shapes! Register those names to be called 
  // back with your instance function
  xmlScene.registerCallback("camera", this);
  xmlScene.registerCallback("light", this);
  xmlScene.registerCallback("shape", this);
  xmlScene.parseFile( filename );
  
}

void Scene::readObjFile( std::string filename ) { 
  // Right now, your code only supports cameras 
  // and shapes! Register those names to be called 
  // back with your instance function
  cam.setDefault();
  cam.position.set(0.0, 0.0, 5.0);
  lightData ldata;
  ldata.setDefault();
  addLight( new lightData( ldata ) );
  

  // Create shader data
  shaderData *shaderPtr_toReturn;
  shaderPtr_toReturn = new shaderData();
  shaderPtr_toReturn->type = lambertian;
  shaderPtr_toReturn->artistic = artistic;
  shaderPtr_toReturn->kd_diffuse.set(1.0, 1.0, 0.5);
  Lambertian thisLambertian(shaderPtr_toReturn);
  thisLambertian.allShapesPtr = &allShapes;
  shaderPtr_toReturn = new Lambertian(thisLambertian);
  
  
// Store all triangles in the OBJ file in a triangle list
// this is the primary list of all geometry in the 3D model
// that we will build up while iterating over the structures
// in the OBJ file data.
std::vector<Triangle*> triangleList;

// ///////////////////////////////
// the following code is needed for reading the OBJ files and
// parsing out their data.

// After reading in the entire OBJ file, we will keep a list of 
// ALL vertices in the 3D object, these will be stored in the 
// vertexList object. I call it a list for simplicity but
// it is implemented as a STL vector.
std::vector<Vector3D> vertexList;
 
// For efficiency in large 3D models, many vertices can and are
// re-used, especially where multiple triangles meet at a point. This
// is managed by what is called an Indexed Triangle list. The incides
// in this list refer to vertices in the vertexList. Sets of 3 indices
// represent a single triangle.
std::vector<int> indexList;
 
// std::string filename; // need to fill this out yourself!
// std::cerr << "Reading OBJ file: " << filename << "..." << std::endl;
 
// The ModelOBJ class comes from the header model_obj.h. We will
// use this class to read the OBJ file. After it is read, we will
// extract the elements needed to create a list of triangles.
ModelOBJ mOBJ;
if (mOBJ.import( filename.c_str() ))
 std::cout << "...loading successful." << std::endl;
else {
 std::cout << "...unsuccessful! Exiting!" << std::endl;
 exit(EXIT_FAILURE);
}

std::cout << "Number of meshes contained within OBJ: " << mOBJ.getNumberOfMeshes() << std::endl;
std::cout << "Number of triangles contained within OBJ: " << mOBJ.getNumberOfTriangles() << std::endl;

const ModelOBJ::Mesh *pMesh = 0;
const ModelOBJ::Vertex *pVertices = 0;

const int *idxBuffer = mOBJ.getIndexBuffer();

// OBJ files can contain multiple "meshes". Each mesh can contain a
// variety of triangles. Here we will loop over all the meshes and
// extract out all the triangles in each mesh.
for (int mIdx=0; mIdx<mOBJ.getNumberOfMeshes(); mIdx++) {
   // Obtain pointers to the mesh data and the vertex list
   pMesh = &mOBJ.getMesh(mIdx);
   pVertices = mOBJ.getVertexBuffer();

   // Some meshes come with shading data embedded in them, such as
   // diffuse and specular components. I am leaving this out for now,
   // but if you find yourself interested, you could extract the
   // material properties out of the mesh like this:
   // 
   // const ModelOBJ::Material *pMaterial = 0;
   // pMaterial = pMesh->pMaterial;
   // std::cout << "Diffuse component: " << pMaterial->diffuse[0]
   // << ", " << pMaterial->diffuse[1]
   // << ", " << pMaterial->diffuse[2] << std::endl;

   // Iterate over all indices in this mesh
   for (int i=pMesh->startIndex; i<(pMesh->startIndex + pMesh->triangleCount*3); i+=3) {

      // The model_obj.h class contains it's OWN Vertex class. We
      // extract the three vertices using the indices here to make it
      // obvious where the data is coming from
      ModelOBJ::Vertex v0, v1, v2;
      v0 = pVertices[ idxBuffer[i] ];
      v1 = pVertices[ idxBuffer[i+1] ];
      v2 = pVertices[ idxBuffer[i+2] ];
 
      // Place these three vertices into our Vector3D class which is
      // used for the Triangle class.
      Vector3D tv0(v0.position[0],v0.position[1],v0.position[2]);
      Vector3D tv1(v1.position[0],v1.position[1],v1.position[2]);
      Vector3D tv2(v2.position[0],v2.position[1],v2.position[2]);

      // Note that with the following step, we are losing the
      // efficiency of the indexed triangle list since we end up making
      // individual triangles without sharing data. If you are
      // interested in changing this in your own code, go for it! Let me
      // know if you do this!
      // 
      // Using the actual vertices of the triangle, instance a new triangle!
      Triangle *tPtr = new Triangle( tv0, tv1, tv2 );
      (*tPtr).shader = shaderPtr_toReturn;

      // In case you're interested, the OBJ files also provide the
      // normal vectors at each vertex. You can access them like this:
      // 
      // v0.normal[0]
      // v0.normal[1]
      // v0.normal[2]
      // and so on for each vertex

      // be sure to add this triangle onto the triangle list
      triangleList.push_back(tPtr);
      
    } 
  }

  addShape(triangleList);
}

void Scene::instance( ptree::value_type const &v )
{
  std::istringstream buf;

  //
  // Scene Parameters
  //
  if (v.first == "sceneParameters") {

    sceneParamData spData;
    // LookAtPoint and ViewDir are optional, but one should be specified.
    boost::optional<std::string> pBGColor = v.second.get_optional<std::string>("bgColor");
    boost::optional<std::string > pEnvMapPrefix = v.second.get_optional<std::string>("envMapPrefix");

    if (pBGColor) {
      buf.str( *pBGColor );
      buf >> spData.backgroundColor;
      buf.clear();
    } 

    if (pEnvMapPrefix) {
      buf.str( *pEnvMapPrefix );
      buf >> spData.envMapPrefix;
      buf.clear();
      
      spData.usesEnvMap = true;
    }
    else {
      spData.usesEnvMap = false;
    }
  }

  //
  // CAMERA
  //
  if (v.first == "camera") {

    std::string name, type;
    Vector3D position, viewDir, lookatPoint;
    bool lookatSet = false;
    float focalLength;
    float imagePlaneWidth;

    name = v.second.get<std::string>("<xmlattr>.name");
    type = v.second.get<std::string>("<xmlattr>.type");

    buf.str( v.second.get<std::string>("position") );
    buf >> position;
    buf.clear();

    // LookAtPoint and ViewDir are optional, but one should be specified.
    boost::optional<std::string> plookatPoint = v.second.get_optional<std::string>("lookatPoint");
    boost::optional<std::string > pviewDir = v.second.get_optional<std::string>("viewDir");

    if (plookatPoint) {
      lookatSet = true;
      buf.str( *plookatPoint );
      buf >> lookatPoint; 
      buf.clear();
    } else if (pviewDir) {
      buf.str( *pviewDir );
      buf >> viewDir; 
      buf.clear();
    }

    buf.str( v.second.get<std::string>("focalLength") );
    buf >> focalLength;
    buf.clear();

    buf.str( v.second.get<std::string>("imagePlaneWidth") );
    buf >> imagePlaneWidth;
    buf.clear();

    if (lookatSet) {
      viewDir = lookatPoint - position;
      viewDir.normalize();
    }
    
    cam.position = position;
    cam.gazeDirection = viewDir;
    cam.focalLength = focalLength;
    cam.imagePlaneWidth = imagePlaneWidth;
        
    if (type == "perspective")
      cam.type = perspective;
    else if (type == "orthographic")
      cam.type = orthographic;

    // Instance the camera here!
    std::cout << "Found Camera!" << std::endl;
  }


  //
  // Light
  //
  if (v.first == "light") {

    std::string type;
    sivelab::Vector3D position, intensity;

    type = v.second.get<std::string>("<xmlattr>.type");

    buf.str( v.second.get<std::string>("position") );
    buf >> position;
    buf.clear();

    buf.str( v.second.get<std::string>("intensity") );
    buf >> intensity;
    buf.clear();

    lightData ldata;
    ldata.position = position;
    ldata.intensity = intensity;

    if (type == "point") {
        ldata.type = point;
    }
    else if (type == "area") {

      sivelab::Vector3D normal;
      buf.str( v.second.get<std::string>("normal") );
      buf >> normal;
      buf.clear();

      float width = 1.0, length = 1.0;
      width = v.second.get<float>("width");
      length = v.second.get<float>("length");

      ldata.normal = normal;
      ldata.width = width;
      ldata.length = length;
      ldata.randomrate = pow(sampleRate, 2);
      ldata.lightSampling();
    }
    // Instance the camera here!
    std::cout << "Found Light!" << std::endl;
    addLight( new lightData( ldata ) );
  }

  // 
  // Shader
  // 
  if (v.first == "shader") {
    parseShaderData(v);
  }

  // 
  // Shape or Instance
  // 
  if (v.first == "shape" || v.first == "instance") {
    parseShapeData(v);
  }

  // Texture
  if (v.first == "texture") {
      std::cout << "Found texture, but not parsing yet..." << std::endl;
  }
}

void Scene::parseShapeData( ptree::value_type const &v )
{
  bool notInstance = true;
  if (v.first == "instance")
    notInstance = false;

  // Shapes and instances are basically the same thing, but need to be
  // added to different structures within the scene

  std::string type, name;
  type = v.second.get<std::string>("<xmlattr>.type");
  name = v.second.get<std::string>("<xmlattr>.name");

  // Make sure to find the shader data objects; HAVE to include a
  // shader in this version; Need to find the shader in the second part
  // of the shape pair
  shaderData *shaderPtr = 0;
  ptree::const_assoc_iterator it = v.second.find("shader");
  if( it != v.second.not_found() )
    {
      shaderPtr = parseShaderData( *it );
    }
    
  shapeData shape;

  std::istringstream buf;
  if (type == "sphere") {
    float radius;
    sivelab::Vector3D center;

    buf.str( v.second.get<std::string>("center") );
    buf >> center;
    buf.clear();

    radius = v.second.get<float>("radius");

    shape.type = sphere;
    shape.name = name;
    shape.radius = radius;
    shape.center = center;
    shape.shader = shaderPtr;
    std::cout << "Found sphere!" << std::endl;
    if(!rasterize)
    {
      addShape( new Sphere(shape));
    }
    else
    {
      Sphere thisSphere(shape);
      thisSphere.rasterize();
      for (std::vector<shapeData*>::iterator shPtr = thisSphere.allTriangles.begin(); shPtr!= thisSphere.allTriangles.end();shPtr++)
      {
        // std::cout << (**shPtr).v0 << " " << (**shPtr).v1 << " " << (**shPtr).v2 << std::endl;
        addShape( new Triangle(**shPtr) );
      }
    }
    
  }

  if (type == "box") {

    sivelab::Vector3D minPt, maxPt;

    buf.str( v.second.get<std::string>("minPt") );
    buf >> minPt;
    buf.clear();

    buf.str( v.second.get<std::string>("maxPt") );
    buf >> maxPt;
    buf.clear();

    shape.type = triangle;
    shape.name = name;
    shape.minPt = minPt;
    shape.maxPt = maxPt;
    shape.shader = shaderPtr;
    shape.isSet = false;

    std::cout << "Found box!" << std::endl;
    Box thisBox(shape);
    for (std::vector<shapeData*>::iterator shPtr = thisBox.allTriangles.begin(); shPtr!= thisBox.allTriangles.end();shPtr++)
    {
      addShape( new Triangle(**shPtr) );
    }
  }

  if (type == "triangle") {
    sivelab::Vector3D v0, v1, v2;

    buf.str( v.second.get<std::string>("v0") );
    buf >> v0;
    buf.clear();

    buf.str( v.second.get<std::string>("v1") );
    buf >> v1;
    buf.clear();

    buf.str( v.second.get<std::string>("v2") );
    buf >> v2;
    buf.clear();

    shape.type = triangle;
    shape.name = name;
    shape.v0 = v0;
    shape.v1 = v1;
    shape.v2 = v2;
    shape.shader = shaderPtr;
    shape.isSet = false;

    std::cout << "Found triangle!" << std::endl;
    addShape( new Triangle(shape));
  }
}

void Scene::addShape( shapeData* shape )
{
  allShapes.push_back(shape);
}

void Scene::addShape( std::vector<Triangle*> triangleList )
{
  for (std::vector<Triangle*>::iterator tPtr = triangleList.begin(); tPtr!= triangleList.end();tPtr++)
  {
    addShape( new Triangle(**tPtr) );
  }
}

void Scene::addLight( lightData* light )
{
  allLights.push_back(light);
}

shaderData* Scene::parseShaderData( ptree::value_type const &v )
{
  std::string type, name;
  shaderData* shaderPtr_toReturn = 0;

  std::istringstream buf;
  boost::optional<std::string> optShaderRef = v.second.get_optional<std::string>("<xmlattr>.ref");

  if (!optShaderRef) {
    type = v.second.get<std::string>("<xmlattr>.type");
    name = v.second.get<std::string>("<xmlattr>.name");
  }

  // if name exists in the shader map and this is a ref, return the shader pointer
  // otherwise, add the shader if it is NOT a ref and the name doesn't exist
  // final is to throw error

  std::map<std::string, shaderData*>::const_iterator mIterator = shaderMap.find(name);
  if (mIterator == shaderMap.end() && !optShaderRef) {
    
    shaderPtr_toReturn = new shaderData();
    // Did not find the shader and it was not a reference, so create and return
    if (type == "Lambertian") {
      
      sivelab::Vector3D kd;
      buf.str( v.second.get<std::string>("diffuse") );
      buf >> kd;
      buf.clear();
      

      shaderPtr_toReturn->type = lambertian;
      shaderPtr_toReturn->kd_diffuse = kd;
      shaderPtr_toReturn->artistic = artistic;
      Lambertian thisLambertian(shaderPtr_toReturn);
      thisLambertian.allShapesPtr = &allShapes;
      
      shaderPtr_toReturn = new Lambertian(thisLambertian);
    }
    else if (type == "BlinnPhong" || type == "Phong") {
      sivelab::Vector3D d, s;
      float phongExp;

      buf.str( v.second.get<std::string>("diffuse") );
      buf >> d;
      buf.clear();

      buf.str( v.second.get<std::string>("specular") );
      buf >> s;
      buf.clear();

      phongExp = v.second.get<float>("phongExp");
      shaderPtr_toReturn->kd_diffuse = d;
      shaderPtr_toReturn->ks_specular = s;
      shaderPtr_toReturn->phongExp = phongExp;

      if (type == "BlinnPhong") {
          shaderPtr_toReturn->type = blinnphong;
          Blinn_phong thisblinn(shaderPtr_toReturn);
          thisblinn.allShapesPtr = &allShapes;

          shaderPtr_toReturn = new Blinn_phong(thisblinn);
      }
      else {
          shaderPtr_toReturn->type = phong;
          Phong thisPhong(shaderPtr_toReturn);
          thisPhong.allShapesPtr = &allShapes;

          shaderPtr_toReturn = new Phong(thisPhong);
      }
    }

    else if (type == "Mirror") {
      shaderPtr_toReturn->type = mirror;
      Mirror thisMirror(shaderPtr_toReturn);
      thisMirror.allShapesPtr = &allShapes;
      thisMirror.mirrorCoef = 1.0f;
      try
      {
        buf.str( v.second.get<std::string>("mirrorCoef") );
        // if a reflection coef is not provided, it is assumed to be a perfect mirror
        float mirrorCoef;
        buf >> mirrorCoef;
        buf.clear();

        // change mirror coef
        thisMirror.mirrorCoef = mirrorCoef;
      }
      catch(const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path> >){}
      

      shaderPtr_toReturn = new Mirror(thisMirror);
    }

    else if (type == "Glaze") {
      sivelab::Vector3D kd;
      buf.str( v.second.get<std::string>("diffuse") );
      buf >> kd;
      buf.clear();

      shaderPtr_toReturn->type = glaze;
      shaderPtr_toReturn->kd_diffuse = kd;
      Glaze thisGlaze(shaderPtr_toReturn);
      thisGlaze.allShapesPtr = &allShapes;
      thisGlaze.mirrorCoef = 1.0f;
      try
      {
        buf.str( v.second.get<std::string>("mirrorCoef") );
        // if a reflection coef is not provided, it is assumed to be a perfect mirror
        float mirrorCoef;
        buf >> mirrorCoef;
        buf.clear();

        // change mirror coef
        thisGlaze.mirrorCoef = mirrorCoef;
      }
      catch(const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path> >){}
      


      shaderPtr_toReturn = new Glaze(thisGlaze);
    }

    else if (type == "Dielectric") {
      shaderPtr_toReturn->type = dielectric;
      Dielectric thisDielectric(shaderPtr_toReturn);
      thisDielectric.allShapesPtr = &allShapes;
      thisDielectric.refrIndex =  1.51; //refractive index of water is 1.333. This will be default! try 1.01 or 0.9999
      thisDielectric.ar = 0.4; thisDielectric.ag = 0.5; thisDielectric.ab = 0.4; // default values

      // get refractive index
      try
      {
        
        buf.str( v.second.get<std::string>("refractiveIndex") );
        // if the refractive index is not given, it uses that of water
        float refrIndex;
        buf >> refrIndex;
        buf.clear();

        // change mirror coef
        thisDielectric.refrIndex = refrIndex;
      }
      catch(const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path> >){}
      
      // get mirror coef
      try
      {
        buf.str( v.second.get<std::string>("attenuationCoef") );
        // if attenuiation coefficients are provided!
        sivelab::Vector3D attCoef;
        buf.str( v.second.get<std::string>("attenuationCoef") );
        buf >> attCoef;
        buf.clear();

        // change mirror coef
        thisDielectric.ar = attCoef[0];
        thisDielectric.ag = attCoef[1];
        thisDielectric.ab = attCoef[2];
      }
      catch(const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path> >){}
      

      shaderPtr_toReturn = new Dielectric(thisDielectric);
    }
    shaderPtr_toReturn->name = name;
    shaderMap[name] = shaderPtr_toReturn;
    
    return shaderPtr_toReturn;
  }
  
  else if (optShaderRef) {
    
    // optShaderRef is true, so this should be a shader reference.
    // Attempt to find the shader in the map and return it.
    std::map<std::string, shaderData*>::const_iterator mIterator = shaderMap.find( *optShaderRef );
    if (mIterator != shaderMap.end())
      return mIterator->second;
    else 
      return 0;
  }
  else 
    std::cerr << "Error that should be caught!" << std::endl;

  return 0;
}

// Raytracer of renderer function!!
void Scene::raytraceRenderer ( std::string filename, int nX, int nY )
{
  // New image object
  png::image< png::rgb_pixel > imData( nX, nY );

  cameraData *this_CamPtr;
  Vector3D objectColor;
  
  float dfield = cam.position[2] - cam.focalLength - depthOfFieldDistance; // Because the camera is looking in the -w/-z directions
  // rpp is the number of stratified sampling to generate
  double epislom;
  
  //compute left, bottom and top, right
  float left = -cam.imagePlaneWidth/2;
  float right = cam.imagePlaneWidth/2;
  
  int divide = 1;
  Ray r;  //Instantiate the ray object
  Ray shadowRay;  //Instantiate the shadow ray object
  float top = right;
  float bottom = left;

  //depthOfFieldDistance
  float distance;
  int countOf;
  
  if(cam.type == perspective ) //perspective camera
  {
    perspectiveCam per_Cam(cam);
    per_Cam.orthonormalBasis( ); //construct camera's orthonormal basis
    per_Cam.setCoordinates( r );
    this_CamPtr = new perspectiveCam(per_Cam);
    
  }
  else
  {
    orthographicCam ortho_Cam(cam);
    ortho_Cam.orthonormalBasis( ); //construct camera's orthonormal basis
    ortho_Cam.setCoordinates( r );
    this_CamPtr = new orthographicCam(ortho_Cam);
  }

  // create hit structure
  HitStruct hstruct;
  hstruct.sampleRate = pow(sampleRate, 2);
  
  // for each pixel, compute color
  for (int j = 0; j < nY; ++j) {
    for (int i = 0; i < nX; ++i) { 

      //depth of field
      distance = 0.0f;
      objectColor = depthColor (this_CamPtr, hstruct, r, left, right, j, i, nX, nY, distance);
      if(depthOfFieldDistance) // checks if depth of field distance parameter is provide
      {
        if (distance < dfield) // checks if hit distance is far from depth of field distance
        {
          Vector3D tempColor(0.0f, 0.0f, 0.0f);
          int a = 0, b = 0, c = nY-1, d = nX-1;

          if (j > 5)
            a = j - 5;
          if (i > 5)
            b = i - 5;
          if (j < nY-5)
            c = j + 5;
          if (i < nX - 5)
            d = i + 5;
          int size = 0;
          for (int q = a; q < c; ++q) {
            for (int u = b; u < d; ++u) { 
              tempColor += depthColor (this_CamPtr, hstruct, r, left, right, q, u, nX, nY, distance);
              size++;
            }
          }
          objectColor = tempColor/size;
        }
      }
      imData[j][i] = png::rgb_pixel(objectColor[0], objectColor[1], objectColor[2]);
      
    }
  }
  // Create visualized image
  imData.write( filename + ".png" );
  
}

Vector3D Scene::depthColor (cameraData *this_CamPtr, HitStruct hstruct, Ray r, float left, float right, int j, int i, int nX, int nY, float &distance)
{
  shapeData shape;
  bool hit;

  // cast ray beyond the object to get depth color
  float epislom, tmin, tmax;
  Vector3D objectColor, ptIntersect, surfaceNorm, bkgColor(0.05, 0.05, 0.05);
  objectColor.set(0.0f,0.0f,0.0f);
  
  distance = 0.0f;
  int countOf = 0;

  // since the image is square and to be simpler
  float top = right;
  float bottom = left;
  r.w = cam.focalLength;
        
  for (int p = 0; p < rpp; p++)
  {
    for (int q = 0; q < rpp; q++)
    {
      epislom = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1));
      
      r.u = left + (right - left) * (i + ((p + epislom)/rpp))/nX;
      r.v = bottom + (top - bottom) * (j + ((q + epislom)/rpp))/nY;

      //  compute ray direction
      this_CamPtr->computeRay(r);
      tmin = 1.0f; tmax = INFINITY; // closest intersection is set to infinity
      hit = false;
      getHitStructure(r, tmin, tmax, shape, hit);
      // Shape color debugging mode
      // std::cout << shape.v0 << std::endl;
      if(hit == true)
      { 
        ptIntersect = shape.getpointIntersect(r, tmax);
        distance += ptIntersect[2]; // depth of Field variables...
        countOf++; // depth of Field variables...
        hstruct.set( allLights, r.direction, (r.origin - ptIntersect), ptIntersect, shape.shapeNormal(ptIntersect), tmin, tmax);
        tempDepth = recursionDepth;
        (shape.shader)->depthPtr = &tempDepth;
        // apply shader
        objectColor += (shape.shader)->apply(hstruct);
      }
      else
      {
        //set to background color
        objectColor += bkgColor;
      }
    }
  }

  distance = distance/countOf;

  objectColor = objectColor / pow(rpp, 2);
  objectColor.set(objectColor[0]*255, objectColor[1]*255, objectColor[2]*255);
  return objectColor;
}

// compute nearest object
void Scene::getHitStructure(Ray r, float tmin, float &tmax, shapeData& tshape, bool &hit)
{
  for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
  {
    (*sptr)->intersect(r, tmin, tmax, tshape, hit);
  }
}



/*********** OPENGL Rasterization Stuff  **************/
void Scene::computeMinMax(std::vector<Vec4*> vertexBufferObject, double &x_min, double &x_max, double &y_min, double &y_max)
{
    for (std::vector<Vec4*>::iterator vptr = vertexBufferObject.begin(); vptr!= vertexBufferObject.end(); vptr++)
    {
        if ((*vptr)->data[0] < x_min)
        {
        x_min = (*vptr)->data[0];
        }
        if ((*vptr)->data[0] > x_max)
        {
        x_max = (*vptr)->data[0];
        }
        if ((*vptr)->data[1] < y_min)
        {
        y_min = (*vptr)->data[1];
        }
        if ((*vptr)->data[1] > y_max)
        {
        y_max = (*vptr)->data[1];
        }
    }
};

void Scene::rasterizeRenderer(std::string filename, int width, int height)
{
  // create new image object
  png::image< png::rgb_pixel > imData( width, height );

  Vector3D gl_Position;

  // set camera
  cam.orthonormalBasis( );

  //Mat4 Mvp, Mortho, Cam.Mp;
  cam.setMortho(-0.5f, 1.0f, -1.5f, 1.5f, -1.5f, 1.5f);
  //cam.setMortho(-1.0f, 1.0f, -1.2f, 1.2f, -1.2f, 1.2f);
  cam.setMvp(width, height);
  cam.setMcam();
  Mat4 vCam = cam.Mcam;
  cam.setMlocal();
  Mat4 Mp;
  Mp.setIdentity();
  
  // Create New Vertex and Vec4 placeholder
  Vertex thisVertex;
  Vec4 thisVec4, lightVec4;

  // DEBUG:: change camera position
  thisVec4.set(cam.position[0], cam.position[1], cam.position[2], 1.0f);
  thisVec4 * cam.Mcam;
  cam.position.set(thisVec4[0], thisVec4[1], thisVec4[2]);
    // change camera position

  // color component
  Vector3D color, c0, c1, c2;
  HitStruct hstruct;

  //make a zbuffer look up table
  double ZBUffer[width][height] = {INFINITY};

  for (int i = 0; i < width; i++)
  {
      for (int j = 0; j < height; j++)
      {
          ZBUffer[i][j] = INFINITY;
      }
  }

  double xmin, ymin, xmax, ymax, alpha, beta, gamma, depth;
  bool hit;

  // convert all lights
  lightData ldata;
  for (std::vector<lightData*>::iterator lptr = allLights.begin(); lptr!= allLights.end(); lptr++)
  {
      ldata = **lptr;
      
      lightVec4.set(ldata.position[0], ldata.position[1], ldata.position[2], 1.0f);
      lightVec4 * cam.Mcam; // M * Vcam

      (*lptr)->position.set(lightVec4[0], lightVec4[1], lightVec4[2]);
  }

  hstruct.allLights  = allLights;
  
  // Camera is turned upside down since it renders  object bottom-top
  cam.V = cam.V * -1;
  cam.W = cam.W * -1;
  cam.setMcam();
  

  // for each triangle in the scene
  for (std::vector<shapeData*>::iterator sptr = allShapes.begin(); sptr!= allShapes.end(); sptr++)
  {
      std::vector<Vec4*> vertexBufferObject;
      xmin = INFINITY; ymin = INFINITY; xmax = 0; ymax = 0;

      // compute surface normal
      (*sptr)->shapeNormal(color);
      hstruct.surfaceNormal = (*sptr)->normal;


      //Apply color here...camera scpace
      /*** Vertex 1 ***/
      hstruct.ptIntersect = (*sptr)->v0;
      c0 = (*sptr)->shader->apply(hstruct);

      /*** Vertex 2 ***/
      hstruct.ptIntersect = (*sptr)->v1;
      c1 = (*sptr)->shader->apply(hstruct);

      /*** Vertex 3 ***/
      hstruct.ptIntersect = (*sptr)->v2;
      c2 = (*sptr)->shader->apply(hstruct);
      
      // for each vertex

      /*** Vertex 1 ***/
      thisVec4.set((*sptr)->v0[0], (*sptr)->v0[1], (*sptr)->v0[2], 1);
      thisVec4 * cam.Mlocal; // V * Mlocal
      thisVec4 * cam.Mcam; // v * Mcam
      // M * Vcam
      thisVec4 * Mp; // V * Mp
      thisVec4 * cam.Mortho; // V * Mortho
      thisVec4 * cam.Mvp; // V * Mvp

      // Perspective Divide to handle perspective
      thisVec4[0] = thisVec4[0] / thisVec4[3];
      thisVec4[1] = thisVec4[1] / thisVec4[3];
      thisVec4[2] = thisVec4[2] / thisVec4[3];

      vertexBufferObject.push_back(new Vec4(thisVec4));
      (*sptr)->v0.set(thisVec4[0], thisVec4[1], thisVec4[2]);

      
      /*** Vertex 2 ***/
      thisVec4.set((*sptr)->v1[0], (*sptr)->v1[1], (*sptr)->v1[2], 1);
      thisVec4 * cam.Mlocal; // V * Mlocal
      thisVec4 * cam.Mcam; // v * Mcam
      // M * Vcam
      thisVec4 * Mp; // V * Mp
      thisVec4 * cam.Mortho; // V * Mortho
      thisVec4 * cam.Mvp; // V * Mvp

      // Perspective Divide to handle perspective
      thisVec4[0] = thisVec4[0] / thisVec4[3];
      thisVec4[1] = thisVec4[1] / thisVec4[3];
      thisVec4[2] = thisVec4[2] / thisVec4[3];

      vertexBufferObject.push_back(new Vec4(thisVec4));
      (*sptr)->v1.set(thisVec4[0], thisVec4[1], thisVec4[2]);

      /*** Vertex 3 ***/
      thisVec4.set((*sptr)->v2[0], (*sptr)->v2[1], (*sptr)->v2[2], 1);
      thisVec4 * cam.Mlocal; // V * Mlocal
      thisVec4 * cam.Mcam; // v * Mcam
      // M * Vcam
      thisVec4 * Mp; // V * Mp
      thisVec4 * cam.Mortho; // V * Mortho
      thisVec4 * cam.Mvp; // V * Mvp

      // Perspective Divide to handle perspective
      thisVec4[0] = thisVec4[0] / thisVec4[3];
      thisVec4[1] = thisVec4[1] / thisVec4[3];
      thisVec4[2] = thisVec4[2] / thisVec4[3];

      vertexBufferObject.push_back(new Vec4(thisVec4));
      (*sptr)->v2.set(thisVec4[0], thisVec4[1], thisVec4[2]);

      // Calculate xmin, ymin, xmax and ymax of t' vertices
      computeMinMax(vertexBufferObject, xmin, xmax, ymin, ymax);


      // Rasterize Triangle, t' since each of its vertices has been transformed
      // to screen coordinates and gone through the perspective divide

      for (int x=xmin; x<=xmax; x++)
      {
          for (int y=ymin; y<=ymax; y++)
          {
              // do for each vertex in triangle here...
              // check code later!
              hit = (*sptr)->getVertexIntersections(x, y,  alpha, beta, gamma);
              if(hit == true)
              {
                  depth = ( (alpha * (*(*sptr)).v0[2])  + (beta * (*(*sptr)).v1[2]) + (gamma * (*(*sptr)).v2[2]) );
                  if(depth * -1 < ZBUffer[x][y])
                  {
                      ZBUffer[x][y] = depth * -1;

                      // SET COLOR
                      color = (c0 * alpha) + (c1 * beta) + (c2 * gamma); 

                      // instead of clipping, let's just check for bounds in the image
                      if (x > 0 && y > 0 && x < width && y < height)
                      {
                          imData[y][x] = png::rgb_pixel(color[0]*255, color[1]*255, color[2]*255);
                      }
                      
                  }
              }

              
          }
      }
  }

  // save image to file
  imData.write( filename + "_sWrasterizer.png" );
}