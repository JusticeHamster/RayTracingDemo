#ifndef PINHOLE_CAMERA_HPP
#define PINHOLE_CAMERA_HPP

#include "camera.hpp"

class pinhole_camera : public camera
{
public:
    pinhole_camera();
    vector<ray> ray_generation();
};

#endif // PINHOLE_CAMERA_HPP
