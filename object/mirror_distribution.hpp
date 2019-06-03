#ifndef MIRROR_DISTRIBUTION_HPP
#define MIRROR_DISTRIBUTION_HPP

#include "ray_distribution.hpp"

class mirror_distribution: public ray_distribution
{
public:
    virtual ~mirror_distribution();
    mirror_distribution(ray &parent, glm::vec3 point, glm::vec3 norm);
    std::vector<ray> random(int num) const;
};

#endif // MIRROR_DISTRIBUTION_HPP
