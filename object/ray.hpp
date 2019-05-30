#ifndef RAY_HPP
#define RAY_HPP

#include "glm/glm.hpp"

#include "line.hpp"

class ray: public line
{
private:
    glm::vec3 rgb;
    glm::vec2 image_position;
    double weight;
    unsigned time;
public:
    const static unsigned max_scattering_time = 5; // 改为从loader读取配置文件
    ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, glm::vec2 image_position, double weight, unsigned time);
    virtual ~ray();
    bool is_end() const;
    void intersect_one_time();
};

#endif // RAY_HPP
