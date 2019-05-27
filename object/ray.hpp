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
    const static unsigned max_scattering_time = 5; // 改为从loader读取配置文件
    ray();
    virtual ~ray();
};

#endif // RAY_HPP
