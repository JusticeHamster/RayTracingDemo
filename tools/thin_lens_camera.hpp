#ifndef THIN_LENS_CAMERA_HPP
#define THIN_LENS_CAMERA_HPP

#include "camera.hpp"

class thin_lens_camera: public camera
{
public:
    thin_lens_camera();
    vector<ray> ray_generation();
};

#endif // THIN_LENS_CAMERA_HPP
