#include "mirror_distribution.hpp"
#include "ray.hpp"

mirror_distribution::~mirror_distribution()
{

}

mirror_distribution::mirror_distribution(ray &parent, glm::vec3 point, glm::vec3 norm): ray_distribution(parent, point, norm)
{

}

std::vector<ray> mirror_distribution::random(int num) const
{
    return {};
}
