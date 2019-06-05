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
    std::vector<ray> r;
    glm::vec3 right = -left * PACK_FACTOR;
    glm::vec3 down = -up * PACK_FACTOR;
    glm::vec3 start = position + direction * DISTANCE_FACTOR;
        - right * ((img.get_width() - 1) / 2.f) - down * ((img.get_height() - 1) / 2.f);
    glm::vec3 p = start;
    for (unsigned i = 0; i < img.get_height(); i++) {
        p = start + down * static_cast<float>(i);
        for (unsigned j = 0; j < img.get_width(); j++) {
            r.push_back(ray(position, p - position, glm::vec3(), img, glm::vec2(i, j), 1, 0));
            p += right;
        }
    }
    return r;
}
