#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "glm/glm.hpp"

using namespace glm;

class sphere: public shape
{
private:
    vec3 center;
    double radius;
public:
    sphere();
    vec3 normal(double u, double v);
};

#endif // SPHERE_HPP
