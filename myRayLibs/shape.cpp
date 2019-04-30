#include "shape.h"


Vector3D shapeData::shapeNormal(Vector3D ptIntersect)
{
    if(type == 0)
    {
        normal.set(ptIntersect[0]-center[0], ptIntersect[1]-center[1], ptIntersect[2]-center[2]);
        normal.normalize();
    }
    else if (type == 1)
    {
        if(!isSet)
        {
            Vector3D vU, vV;
            vU = v1 - v0;
            vV = v2 - v0;
            normal = vU.cross(vV);
            normal.normalize();
            isSet = true;
        }
    }
    else{}
    return normal;
}

/*************** THE SPHERE CLASS  ******************/
/*************** Sphere functions  ******************/
Sphere::Sphere(shapeData shape)
{
    type = sphere;
    name = shape.name;
    center = shape.center;
    radius = shape.radius;
    shader = shape.shader;   
};

void Sphere::setParameters(shapeData shape)
{
    type = sphere;
    name = shape.name;
    center = shape.center;
    radius = shape.radius;
    shader = shape.shader;   
};


// sphere intersection
bool Sphere::intersect(Ray r, float tmin, float &tmax, shapeData &tshape, bool &hit)
{
    Vector3D dist;
    float t0, t1, tval, discriminant;
    
    dist = r.origin - center;
    discriminant = pow((r.direction.dot(dist)), 2) - (r.direction.dot(r.direction) * dist.dot(dist) - pow(radius, 2));

     /* If the discriminant is negative, there are no real roots.
    * Return false in that case as the ray misses the sphere.
    * Return true in all other cases (can be one or two intersections)
    * t represents the distance between the start of the ray and
    * the point on the sphere where it intersects.
    */
    if(discriminant < 0)
        return false;
    else
    {
        t0 = (- r.direction.dot(dist) - sqrt(pow(r.direction.dot(dist), 2) - r.direction.dot(r.direction)*(dist.dot(dist) - pow(radius, 2))))/r.direction.dot(r.direction);
        t1 = (- r.direction.dot(dist) + sqrt(pow(r.direction.dot(dist), 2) - r.direction.dot(r.direction)*(dist.dot(dist) - pow(radius, 2))))/r.direction.dot(r.direction);

        if( t0 < tmin )
            t0 = 0.0f;
        if( t1 < tmin )
            t1 = 0.0f;

        if( t0 < t1 )
                tval = t0;
            else
                tval = t1;

            // Verify t0 larger than tmin and less than the tmax
            if(tval >= tmin && tval < tmax){
                tmax = tval;
                tshape = *this;
                hit = true;
                return true;
            }
            return false;
    }
}

// Tesselation process of Sphere
void Sphere::rasterize()
{
    float x, y, z;
    x = center[0] + radius;
    y = center[1] + radius;
    z = center[2] + radius;
    maxPt.set(x, y, z);
    x = center[0] - radius;
    y = center[1] - radius;
    z = center[2] - radius;
    minPt.set(x, y, z);
    std::cout << "radius is: " << radius << std::endl;
    std::cout << "maxpt and minpt: " << maxPt << " " << minPt <<  "and center is : " << center << std::endl;
    Box sphereBox(*this);
    // tesselation(sphereBox);
    allTriangles = sphereBox.allTriangles;
}

void Sphere::tesselation(Box sphereBox)
{
    //Triangle coordinates
    Vector3D c0, c1, c2;
    // subdived points
    Vector3D p0, p1, p2;
    int numOfTimes = 1;
    for (std::vector<shapeData*>::iterator shPtr = sphereBox.allTriangles.begin(); shPtr!= sphereBox.allTriangles.end();shPtr++)
    {
        c0 = (**shPtr).v0;
        c1 = (**shPtr).v0;
        c2 = (**shPtr).v0;
        // Tesselate repeatedly
        p0 = (c0 + c1) / 2.0f;
        p1 = (c1 + c2) / 2.0f;
        p2 = (c0 + c2) / 2.0f;
        
        //p0.set()
        Vector3D tesselatedCoords[] = {};
    }
}
/*************** Sphere functions  ******************/

/*************** THE TRIANGLE CLASS  ******************/
/*************** Triangle functions  ******************/

// Triangle instances
Triangle::Triangle(shapeData shape)
{
    type = triangle;
    name = shape.name;
    shader = shape.shader;
    v0 = shape.v0;
    v1 = shape.v1;
    v2 = shape.v2;
};

Triangle::Triangle(Vector3D t0, Vector3D t1, Vector3D t2)
{
    type = triangle;
    v0 = t0;
    v1 = t1;
    v2 = t2;
};

void Triangle::set(Vector3D t0, Vector3D t1, Vector3D t2)
{
    type = triangle;
    v0 = t0;
    v1 = t1;
    v2 = t2;
};

/*************** Triangle functions  ******************/




/*************** THE BOX CLASS  ******************/
/*************** Box functions  ******************/
Box::Box(shapeData shape)
{
    double min_x, min_y, min_z, max_x, max_y, max_z;
    Vector3D a, b, c;
    Triangle triangleBox(shape);
    type = triangle;
    name = shape.name;
    shader = shape.shader;
    min_x = shape.minPt[0];
    max_x = shape.maxPt[0];
    min_y = shape.minPt[1];
    max_y = shape.maxPt[1];
    min_z = shape.minPt[2];
    max_z = shape.maxPt[2];

    // triangle1
    a.set(max_x, max_y, max_z);
    b.set(max_x, min_y, max_z);
    c.set(max_x, min_y, min_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle2
    a.set(max_x, min_y, min_z);
    b.set(max_x, max_y, min_z);
    c.set(max_x, max_y, max_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle3
    a.set(max_x, max_y, min_z);
    b.set(max_x, min_y, min_z);
    c.set(min_x, min_y, min_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle4
    a.set(min_x, min_y, min_z);
    b.set(min_x, max_y, min_z);
    c.set(max_x, max_y, min_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle5
    a.set(min_x, max_y, min_z);
    b.set(min_x, min_y, min_z);
    c.set(min_x, min_y, max_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle6
    a.set(min_x, min_y, max_z);
    b.set(min_x, max_y, max_z);
    c.set(min_x, max_y, min_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle7
    a.set(max_x, max_y, min_z);
    b.set(min_x, max_y, min_z);
    c.set(min_x, max_y, max_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle8
    a.set(min_x, max_y, max_z);
    b.set(max_x, max_y, max_z);
    c.set(max_x, max_y, min_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle9
    a.set(min_x, min_y, min_z);
    b.set(max_x, min_y, min_z);
    c.set(max_x, min_y, max_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle10
    a.set(max_x, min_y, max_z);
    b.set(min_x, min_y, max_z);
    c.set(min_x, min_y, min_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

     // triangle11
    a.set(min_x, max_y, max_z);
    b.set(min_x, min_y, max_z);
    c.set(max_x, min_y, max_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));

    // triangle10
    a.set(max_x, min_y, max_z);
    b.set(max_x, max_y, max_z);
    c.set(min_x, max_y, max_z);
    triangleBox.set(a, b, c);
    allTriangles.push_back(new Triangle(triangleBox));
}

//shapeData
Vector3D shapeData::getpointIntersect(Ray r, float tmax)
{
    return (r.origin + (tmax*r.direction));
}

// Triangle intersection
bool Triangle::intersect(Ray r, float tmin, float &tmax, shapeData &tshape, bool &hit)
{
    double alpha, beta, gamma, bigM, a, b, c, d, e, f, g, h, i, j, k, l;
    double tval;
    // Using barycentric coordinates to compute point of intersection 
    // and values of alpha, beta & gamma!

    // calculate the 3 x 3 matrix values
    a = v0[0] - v1[0];
    b = v0[1] - v1[1];
    c = v0[2] - v1[2];
    d = v0[0] - v2[0];
    e = v0[1] - v2[1];
    f = v0[2] - v2[2];
    g = r.direction[0];
    h = r.direction[1];
    i = r.direction[2];
    j = v0[0] - r.origin[0];
    k = v0[1] - r.origin[1];
    l = v0[2] - r.origin[2];

    // compute M
    bigM =  (a * ((e*i) - (h*f))) + (b * ((g*f)-(d*i))) + (c * ((d*h) - (e*g)));
    // compute beta
    beta = ((j * ((e*i) - (h*f))) + (k * ((g*f) - (d*i))) + (l * ((d*h) - (e*g)))) / bigM;
    // compute gamma
    gamma = ((i * ((a*k) - (j*b))) + (h * ((j*c) - (a*l))) + (g * ((b*l) - (k*c)))) / bigM;
    // compute tmax
    tval = -1 * ((f * ((a*k) - (j*b))) + (e * ((j*c) - (a*l))) + (d * ((b*l) - (k*c)))) / bigM;

    alpha = 1 - beta - gamma;
    
    //check if true or false
    if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1 || gamma < 0 || gamma > 1)
    {
        return false;
    }
    else
    {
        if (tval >= tmin && tval < tmax)
        {
            
            tshape = (*this);
            tmax = tval;
            hit = true;
            return true;
        }
    }
}

// Initializing triangle with OBJ files
void Triangle::initialize(std::string filename)
{
    numFloatsNeeded = 0;
    ModelOBJ mOBJ;
    if (mOBJ.import( filename.c_str() ))
        std::cout << "OBJ File ...loading successful." << std::endl;
    else {
        std::cout << "...unsuccessful! Exiting!" << std::endl;
    }
    std::cout << "Number of meshes contained within OBJ: " << mOBJ.getNumberOfMeshes() << std::endl;
    std::cout << "Number of triangles contained within OBJ: " << mOBJ.getNumberOfTriangles() << std::endl;

    const ModelOBJ::Mesh *pMesh = 0;
    const ModelOBJ::Vertex *pVertices = 0;

    const int *idxBuffer = mOBJ.getIndexBuffer();

    numFloatsNeeded = mOBJ.getNumberOfTriangles() * 24;
    host_VertexBuffer = new float[ numFloatsNeeded ];
    numBytes = (numFloatsNeeded) * sizeof(float);
    
    int tIdx = 0;
    
   for (int mIdx=0; mIdx<mOBJ.getNumberOfMeshes(); mIdx++) {

   // Obtain pointers to the mesh data and the vertex list
   pMesh = &mOBJ.getMesh(mIdx);
   pVertices = mOBJ.getVertexBuffer();

   // Some meshes come with shading data embedded in them, such as
   // diffuse and specular components. I am leaving this out for now,
   // but if you find yourself interested, you could extract the
   // material properties out of the mesh like this:
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

      // compute normal per vertex
      Triangle *tPtr = new Triangle( tv0, tv1, tv2 );
      Vector3D theNormal = tPtr->shapeNormal(tv0);

      // compute per vertex 1
      host_VertexBuffer[ tIdx++ ] = v0.position[0]; 
      host_VertexBuffer[ tIdx++ ] = v0.position[1]; 
      host_VertexBuffer[ tIdx++ ] = v0.position[2]; 
      
      // normal
      host_VertexBuffer[ tIdx++ ] = theNormal[0]; 
      host_VertexBuffer[ tIdx++ ] = theNormal[1]; 
      host_VertexBuffer[ tIdx++ ] = theNormal[2]; 

      // Texture coordinate
      host_VertexBuffer[ tIdx++ ] = 0.0f; 
      host_VertexBuffer[ tIdx++ ] = 0.0f; 

      // compute per vertex 1
      host_VertexBuffer[ tIdx++ ] = v1.position[0]; 
      host_VertexBuffer[ tIdx++ ] = v1.position[1]; 
      host_VertexBuffer[ tIdx++ ] = v1.position[2]; 
      
      // normal
      host_VertexBuffer[ tIdx++ ] = theNormal[0]; 
      host_VertexBuffer[ tIdx++ ] = theNormal[1]; 
      host_VertexBuffer[ tIdx++ ] = theNormal[2]; 

      // Texture coordinate
      host_VertexBuffer[ tIdx++ ] = 1.0f; 
      host_VertexBuffer[ tIdx++ ] = 0.0f; 
      
      // compute per vertex 1
      host_VertexBuffer[ tIdx++ ] = v2.position[0]; 
      host_VertexBuffer[ tIdx++ ] = v2.position[1]; 
      host_VertexBuffer[ tIdx++ ] = v2.position[2]; 
      
      // normal
      host_VertexBuffer[ tIdx++ ] = theNormal[0]; 
      host_VertexBuffer[ tIdx++ ] = theNormal[1]; 
      host_VertexBuffer[ tIdx++ ] = theNormal[2]; 

      // Texture coordinate
      host_VertexBuffer[ tIdx++ ] = 0.0f; 
      host_VertexBuffer[ tIdx++ ] = 1.0f; 

      
    } 
  }

  std::cout << "The value of tidx is : " << tIdx << " & floats is : " << numFloatsNeeded << std::endl;

}


// OPENGL stuff
bool shapeData::getVertexIntersections(float xaxis, float yaxis, double &alpha, double &beta, double &gamma)
{
    double bigM, a, b, c, d, e, f, g, h, i, j, k, l, tval; // tval;
    // Using barycentric coordinates to compute point of intersection 
    // and values of alpha, beta & gamma!

    // calculate the 3 x 3 matrix values
    a = v0[0] - v1[0];
    b = v0[1] - v1[1];
    c = 0;
    d = v0[0] - v2[0];
    e = v0[1] - v2[1];
    f = 0;
    g = xaxis;
    h = yaxis;
    i = 1;
    j = v0[0];
    k = v0[1];
    l = 1;

    // compute M
    bigM =  (a * ((e*i) - (h*f))) + (b * ((g*f)-(d*i))) + (c * ((d*h) - (e*g)));
    // compute beta
    beta = ((j * ((e*i) - (h*f))) + (k * ((g*f) - (d*i))) + (l * ((d*h) - (e*g)))) / bigM;
    // compute gamma
    gamma = ((i * ((a*k) - (j*b))) + (h * ((j*c) - (a*l))) + (g * ((b*l) - (k*c)))) / bigM;
    // compute tmax
    tval = -1 * ((f * ((a*k) - (j*b))) + (e * ((j*c) - (a*l))) + (d * ((b*l) - (k*c)))) / bigM;

    alpha = 1 - beta - gamma;

    //check if true or false
    if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1 || gamma < 0 || gamma > 1)
    {
        return false;
    }
    else
        return true;
}