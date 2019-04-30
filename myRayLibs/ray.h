#ifndef _RAY_H
#define _RAY_H

#include "Vector3D.h"

using namespace sivelab;

class Ray {
	public:
		Vector3D U, V, W, origin, direction, lightIntersect, surfaceNormal;
		float u, v, w;
};

#endif