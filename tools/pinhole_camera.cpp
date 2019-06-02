#include "pinhole_camera.hpp"

pinhole_camera::pinhole_camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up):
    camera(width, height, position, direction, up)
{

}

pinhole_camera::~pinhole_camera()
{

}

std::vector<ray> pinhole_camera::ray_generation()
{
    return { ray(glm::vec3(), glm::vec3(1, 1, 1), glm::vec3(), img, glm::vec2(0, 0), 1, 0) };
}
