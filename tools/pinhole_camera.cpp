#include "pinhole_camera.hpp"

pinhole_camera::pinhole_camera(): camera(0, 0)
{

}

pinhole_camera::~pinhole_camera()
{

}

std::vector<ray> pinhole_camera::ray_generation()
{
    return { ray(glm::vec3(), glm::vec3(1, 1, 1), glm::vec3(), img, glm::vec2(0, 0), 1, 0) };
}
