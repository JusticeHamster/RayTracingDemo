#ifndef PHONE_DISTRIBUTION_HPP
#define PHONE_DISTRIBUTION_HPP

#include "ray_distribution.hpp"

#include <algorithm>
#include <random>

class phone_distribution: public ray_distribution
{
private:
    mutable std::mt19937 generator;
    mutable std::normal_distribution<float> normal;
    glm::vec3 random_direction(glm::vec3 main, float limit) const;
    float angle_bound;
    inline glm::vec2 generate(float limit) const;
public:
    virtual ~phone_distribution();
    phone_distribution(ray &parent, glm::vec3 point, glm::vec3 norm, float angle_bound);
    std::vector<ray> random(int num) const;
};

#endif // PHONE_DISTRIBUTION_HPP
