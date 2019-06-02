#include "thin_lens_camera.hpp"

thin_lens_camera::thin_lens_camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up):
    camera(width, height, position, direction, up)
{

}

thin_lens_camera::~thin_lens_camera()
{

}

std::vector<ray> thin_lens_camera::ray_generation()
{
    return {};
}
