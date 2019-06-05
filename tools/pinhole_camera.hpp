#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "camera.hpp"

class pinhole_camera : public camera
{
public:
    constexpr static float PACK_FACTOR = .5f;
    constexpr static float DISTANCE_FACTOR = 2.f;
    pinhole_camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 0, 1));
    virtual ~pinhole_camera();
    std::vector<ray> ray_generation();
};

#endif // PINHOLE_CAMERA_HPP
