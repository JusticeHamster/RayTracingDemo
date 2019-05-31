#ifndef THIN_LENS_CAMERA_HPP
#define THIN_LENS_CAMERA_HPP

#include "camera.hpp"

class thin_lens_camera: public camera
{
public:
    thin_lens_camera();
    virtual ~thin_lens_camera();
    std::vector<ray> ray_generation() const;
};

#endif // THIN_LENS_CAMERA_HPP
