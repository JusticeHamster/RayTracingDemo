#include "ray_distribution.hpp"

ray_distribution::ray_distribution(ray &parent, glm::vec3 point, glm::vec3 norm): parent(parent), point(point), norm(norm)
{

}

ray_distribution::~ray_distribution()
{

}
