#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"
#include "Vector3D.h"
#include "mat4.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace sivelab;

// Camera Initialization Data

enum CamType { 
  perspective, orthographic 
};

struct cameraData {
  CamType type;
  Vector3D position;
  Vector3D gazeDirection;
  Vector3D U, V, W, tnonCollinear;
  float focalLength;
  float imagePlaneWidth;
  float aspectRatio;
  // construct orthonormal basis
  void orthonormalBasis();
  // set the coordinates of the ray origin to that of the camera;
  void setCoordinates(Ray &r);
  // set a default for the camera
  void setDefault();
  // compute the ray at pixel (i, j)
	virtual void computeRay(Ray &r){};

  /******** OPENGL Stuff  ****/

  glm::vec3 glpos; // position with vec3 or OPENGL
  glm::vec3 glU, glW, glV;

  //OPENGL Stuff
  virtual glm::mat4 getProjectionMatrix(){
    float vFOV = 5.0f;
    float focalLength = 0.5f;
    float aspectRatio = 1.0f;
    return glm::perspective(vFOV, aspectRatio, focalLength, 200.0f);
  };
  virtual glm::mat4 getViewMatrix(){
    glU = glm::vec3(1.0f, 0.0f, 0.0f);
    glW = glm::vec3(0.0f, 0.0f, -1.0f);
    glV = glm::vec3(0.0f, -1.0f, 0.0f);
    return glm::lookAt( glpos, glpos - glW, glV );
  };

  glm::vec3 toVec3(Vector3D vector)
  {
    glm::vec3 W = glm::vec3(vector[0], vector[1], vector[2]);
  }

  // Software Rasterizer Stuff
  Mat4 Mvp, Mortho, Mp, Mcam, Mlocal;
  void setMortho(const double near, const double far, const double left, const double right,
  const double top, const double bottom
  )
  {
    Mortho[0] = 2 / (right - left);
    Mortho[3] = -1 * ( (right + left) / (right - left) );
    Mortho[5] = 2 / (top - bottom);
    Mortho[7] = -1 * ( (top + bottom) / (top - bottom) );
    Mortho[10] = 2 / (near - far);
    Mortho[11] = -1 * ( (near + far) / (near - far) );
    Mortho[15] = 1;
  };

  void setMvp(const double nX, const double nY)
  {
    Mvp[0] = nX / 2;
    Mvp[3] = ( nX - 1 ) / 2;
    Mvp[5] = nY/ 2;
    Mvp[7] = ( nY - 1 ) / 2;
    Mvp[10] = 1;
    Mvp[15] = 1;
  };

  void setMcam()
  {
    Mcam[0] = U[0];
    Mcam[1] = U[1];
    Mcam[2] = U[2];
    Mcam[4] = V[0];
    Mcam[5] = V[1];
    Mcam[6] = V[2];
    Mcam[8] = W[0];
    Mcam[9] = W[1];
    Mcam[10] = W[2];
    Mcam[15] = 1;
    //Mcam.transpose();
  };

  void setMlocal()
  {
    Mlocal[0] = 1;
    Mlocal[3] = -1 * position[0];
    Mlocal[5] = 1;
    Mlocal[7] = -1 * position[1];
    Mlocal[10] = 1;
    Mlocal[11] = -1 * position[2];
    Mlocal[15] = 1;
  }

};

class perspectiveCam : public cameraData
{
	private:
	public:
  perspectiveCam(){}; // default constructor
  ~perspectiveCam(){}; // default destructor
  perspectiveCam(cameraData cam);
	void computeRay(Ray &r);
};

class orthographicCam : public cameraData
{
	private:
	public:
    orthographicCam(){}; // default constructor
    ~orthographicCam(){}; // default destructor
    orthographicCam(cameraData cam);
	// compute the ray at pixel (i, j)
	void computeRay(Ray &r);
};

#endif
