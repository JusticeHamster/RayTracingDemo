#include "diffuse_distribution.hpp"
#include "ray.hpp"

diffuse_distribution::~diffuse_distribution()
{

}

diffuse_distribution::diffuse_distribution(ray &parent, glm::vec3 point, glm::vec3 norm): ray_distribution(parent, point, norm)
{

}

std::vector<ray> diffuse_distribution::random(int num) const
{
    return { ray(point, parent.direction() + 2.f * norm, glm::vec3(), parent.get_img(), parent.get_img_position(), 1, parent.get_time() + 1) };
}
