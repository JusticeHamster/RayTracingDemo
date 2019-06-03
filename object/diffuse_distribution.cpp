#include "diffuse_distribution.hpp"
#include "ray.hpp"

diffuse_distribution::~diffuse_distribution()
{

}

diffuse_distribution::diffuse_distribution(ray &parent, glm::vec3 point): ray_distribution(parent, point)
{

}

std::vector<ray> diffuse_distribution::random(int num) const
{
    return { ray(glm::vec3(), glm::vec3(0, 1, 0), glm::vec3(), parent.get_img(), parent.get_img_position(), 1, parent.get_time() + 1) };
}
