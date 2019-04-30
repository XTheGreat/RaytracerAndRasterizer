#include <math.h>
#include <cstdlib>
#include "camera.h"

void cameraData::setCoordinates(Ray &r)
{
    r.U = U;
    r.V = V;
    r.W = W;
}

void cameraData::orthonormalBasis( )
{
    tnonCollinear.set(0.0f,1.0f,0.0f);

    
    W = -1 * gazeDirection;
    W.normalize();

    // choose a non-collinsear vector t
    U = tnonCollinear.cross(W);
    U.normalize();
    V = U.cross(W);
    V.normalize();   
}

perspectiveCam::perspectiveCam(cameraData cam)
{
    type = cam.type;
    position = cam.position;
    gazeDirection = cam.gazeDirection;
    U = cam.U;
    V = cam.V;
    W = cam.W;
    tnonCollinear = cam.tnonCollinear;
    focalLength = cam.focalLength;
    imagePlaneWidth = cam.imagePlaneWidth;
    aspectRatio = cam.aspectRatio;
};

void perspectiveCam::computeRay(Ray &r)
{
    r.origin = position;
    // compute ray direction
    r.direction = (r.u * r.U) + (r.v * r.V) + (-r.w * r.W);
}




void cameraData::setDefault()
{
    type = perspective;
    position.set(0, 0, -5);
    gazeDirection.set(0,0,-1);
    focalLength = 1.0f;
    imagePlaneWidth = 0.5f;
    orthonormalBasis( );
}

orthographicCam::orthographicCam(cameraData cam)
{
    type = cam.type;
    position = cam.position;
    gazeDirection = cam.gazeDirection;
    U = cam.U;
    V = cam.V;
    W = cam.W;
    tnonCollinear = cam.tnonCollinear;
    focalLength = cam.focalLength;
    imagePlaneWidth = cam.imagePlaneWidth;
    aspectRatio = cam.aspectRatio;
};

void orthographicCam::computeRay(Ray &r)
{
    r.origin = position + (r.u * r.U) + (r.v * r.V);
    // compute ray direction
    r.direction = -1 * (r.W);
}