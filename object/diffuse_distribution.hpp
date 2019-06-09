#ifndef DIFFUSE_DISTRIBUTION_HPP
#define DIFFUSE_DISTRIBUTION_HPP

#include <algorithm>
#include <random>

#include "ray_distribution.hpp"

class diffuse_distribution: public ray_distribution
{
private:
    mutable std::mt19937 generator;
    mutable std::uniform_real_distribution<float> uniform;
    glm::vec3 random_direction() const;
    glm::mat4 orientation;
public:
    virtual ~diffuse_distribution();
    diffuse_distribution(ray &parent, glm::vec3 point, glm::vec3 norm);
    std::vector<ray> random(int num) const;
};

#endif // DIFFUSE_DISTRIBUTION_HPP
