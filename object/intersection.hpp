#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "glm/glm.hpp"

using namespace glm;

class ray_distribution;

class intersection
{
private:
    bool is_intersect;
    ray_distribution &out;
    vec3 point;
    vec3 stop_energy;
public:
    intersection(bool is_intersect, ray_distribution &out, vec3 point, vec3 stop_energy);
};

#endif // INTERSECTION_HPP
