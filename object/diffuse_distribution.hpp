#ifndef DIFFUSE_DISTRIBUTION_HPP
#define DIFFUSE_DISTRIBUTION_HPP

#include "ray_distribution.hpp"

class diffuse_distribution: public ray_distribution
{
public:
    virtual ~diffuse_distribution();
    diffuse_distribution(ray &parent, glm::vec3 point, glm::vec3 norm);
    std::vector<ray> random(int num) const;
};

#endif // DIFFUSE_DISTRIBUTION_HPP
