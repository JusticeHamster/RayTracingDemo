#include "pinhole_camera.hpp"

#include "loader.hpp"

pinhole_camera::pinhole_camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up):
    camera(width, height, position, direction, up)
{

}

pinhole_camera::~pinhole_camera()
{

}

std::vector<ray> pinhole_camera::ray_generation()
{
    loader &ldr = loader::instance;
    float pack_factor = ldr.get_factor("pack");
    glm::vec3 right = -left * pack_factor;
    glm::vec3 down = -up * pack_factor;
    glm::vec3 start = position + direction * ldr.get_factor("distance");
        - right * ((img.get_width() - 1) / 2.f) - down * ((img.get_height() - 1) / 2.f);
    glm::vec3 p = start;
    std::vector<ray> r;
    for (unsigned i = 0; i < img.get_height(); i++) {
        p = start + down * static_cast<float>(i);
        for (unsigned j = 0; j < img.get_width(); j++) {
            r.push_back(ray(position, p - position, glm::vec3(), img, glm::vec2(i, j), 1, 0));
            p += right;
        }
    }
    return r;
}
