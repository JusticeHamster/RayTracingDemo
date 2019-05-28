#ifndef RAY_DISTRIBUTION_HPP
#define RAY_DISTRIBUTION_HPP

#include <vector>

#include "glm/glm.hpp"

class ray;

class ray_distribution
{
private:
    glm::vec3 point;
public:
    virtual std::vector<ray> random(int num) const = 0;
    virtual ~ray_distribution();
};

#endif // RAY_DISTRIBUTION_HPP
