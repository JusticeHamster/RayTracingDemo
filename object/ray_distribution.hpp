#ifndef RAY_DISTRIBUTION_HPP
#define RAY_DISTRIBUTION_HPP

#include <vector>

#include "ray.hpp"

#include "glm/glm.hpp"

using namespace std;
using namespace glm;

class ray_distribution
{
private:
    vec3 point;
    // double probability(vec3 direction);
public:
    virtual vector<ray> random(int num) = 0;
};

#endif // RAY_DISTRIBUTION_HPP
