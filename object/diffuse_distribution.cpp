#include "diffuse_distribution.hpp"
#include "ray.hpp"

#include <algorithm>
#include <random>

diffuse_distribution::~diffuse_distribution()
{

}

diffuse_distribution::diffuse_distribution(ray &parent, glm::vec3 point, glm::vec3 norm): ray_distribution(parent, point, norm)
{

}

static std::random_device random_device;
static std::mt19937 generator(random_device());

std::vector<ray> diffuse_distribution::random(int num) const
{
    if (parent.is_inside())
        return {};
    std::vector<ray> rays;
    float weight = 1.f / num;
    for (int i = 0; i < num; i++) {
        float u = generator(), v = generator();
        float phi = u * shape::PI2, theta = v * shape::PI;
        float x = glm::sin(theta) * glm::cos(phi);
        float y = glm::sin(theta) * glm::sin(phi);
        float z = glm::cos(theta);
        rays.push_back(ray(point, glm::vec3(x, y, z), glm::vec3(), parent.get_img(), parent.get_img_position(), weight, parent.get_time() + 1, parent.is_inside()));
    }
    return rays;
}
