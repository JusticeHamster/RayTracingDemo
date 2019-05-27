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
public:
    virtual vector<ray> random(int num) const = 0;
    virtual ~ray_distribution();
};

#endif // RAY_DISTRIBUTION_HPP
