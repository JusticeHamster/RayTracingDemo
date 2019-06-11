#include "diffuse_distribution.hpp"
#include "ray.hpp"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "tools/printer.hpp"

glm::vec3 diffuse_distribution::random_direction() const
{
    float u = uniform(generator), v = uniform(generator);
    float phi = (u - .5f) * shape::PI, theta = v * shape::PI2;
    float x = glm::sin(phi) * glm::cos(theta);
    float y = glm::sin(phi) * glm::sin(theta);
    float z = glm::cos(phi);
    return glm::vec4(x, y, z, 0) * orientation;
}

diffuse_distribution::~diffuse_distribution()
{

}

static std::random_device random_device;

diffuse_distribution::diffuse_distribution(ray &parent, glm::vec3 point, glm::vec3 norm): ray_distribution(parent, point, norm), generator(random_device())
{
    glm::vec3 origin(0, 0, 1);
    float angle = glm::dot(norm, origin);
    glm::vec3 rotate_axis = glm::cross(norm, origin);
    orientation = glm::rotate(glm::mat4(1.), glm::acos(angle), rotate_axis);
}

std::vector<ray> diffuse_distribution::random(int num) const
{
    if (parent.is_inside())
        return {};
    std::vector<ray> rays;
    float weight = 1.f / num;
    for (int i = 0; i < num; i++) {
        rays.push_back(ray(point, random_direction(), glm::vec3(), parent.get_img(), parent.get_img_position(), weight, parent.get_time() + 1, parent.is_inside()));
    }
    return rays;
}
