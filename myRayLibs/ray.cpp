#include "ray.h"



/******
 * 
bool Ray::sphereIntersect (float tmin, float &tmax, shapeData &tshape, Sphere shape, bool &hit)
{
    dist = origin - shape.center;
    discriminant = pow((direction.dot(dist)), 2) - (direction.dot(direction) * dist.dot(dist) - pow(shape.radius, 2));

    if(discriminant < 0)
        return false;
    else
    {
        float t0 = (- direction.dot(dist) - sqrt(pow(direction.dot(dist), 2) - direction.dot(direction)*(dist.dot(dist) - pow(shape.radius, 2))))/direction.dot(direction);
        float t1 = (- direction.dot(dist) + sqrt(pow(direction.dot(dist), 2) - direction.dot(direction)*(dist.dot(dist) - pow(shape.radius, 2))))/direction.dot(direction);

        if(t0 < t1)
                tval = t0;
            else
                tval = t1;

            // Verify t0 larger than tmin and less than the tmax
            if(tval >= tmin && tval < tmax){
                tmax = tval;
                tshape = shape;
                hit = true;
                return true;
            }
            return false;
    }
}

bool Ray::triangleIntersect (float tmin, float &tmax, shapeData &tshape, Triangle shape, bool &hit)
{
    // Using barycentric coordinates to compute point of intersection 
    // and values of alpha, beta & gamma!

    // calculate the 3 x 3 matrix values
    a = shape.v0[0] - shape.v1[0];
    b = shape.v0[1] - shape.v1[1];
    c = shape.v0[2] - shape.v1[2];
    d = shape.v0[0] - shape.v2[0];
    e = shape.v0[1] - shape.v2[1];
    f = shape.v0[2] - shape.v2[2];
    g = direction[0];
    h = direction[1];
    i = direction[2];
    j = shape.v0[0] - origin[0];
    k = shape.v0[1] - origin[1];
    l = shape.v0[2] - origin[2];

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
            tmax = tval;
            tshape = shape;
            hit = true;
            return true;
        }
    } 
}


****/