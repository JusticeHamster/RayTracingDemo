#include "thin_lens_camera.hpp"

thin_lens_camera::thin_lens_camera(): camera(0, 0)
{

}

thin_lens_camera::~thin_lens_camera()
{

}

std::vector<ray> thin_lens_camera::ray_generation() const
{
    return {};
}
