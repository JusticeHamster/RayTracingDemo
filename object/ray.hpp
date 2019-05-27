#ifndef RAY_HPP
#define RAY_HPP

#include "glm/glm.hpp"
#include "line.hpp"

using namespace glm;

class ray: public line
{
private:
    vec3 rgb;
    vec2 image_position;
    double weight;
    unsigned time;
public:
    const static unsigned max_scattering_time = 5;
    ray();
};

#endif // RAY_HPP
