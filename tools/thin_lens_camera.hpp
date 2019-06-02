#ifndef THIN_LENS_CAMERA_HPP
#define THIN_LENS_CAMERA_HPP

#include "camera.hpp"

class thin_lens_camera: public camera
{
public:
    thin_lens_camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 0, 1));
    virtual ~thin_lens_camera();
    std::vector<ray> ray_generation();
};

#endif // THIN_LENS_CAMERA_HPP
