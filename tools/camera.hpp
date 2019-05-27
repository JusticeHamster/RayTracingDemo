#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>

#include "object/ray.hpp"

class camera
{
protected:
    unsigned width, height;
    camera(unsigned width, unsigned height);
public:
    virtual std::vector<ray> ray_generation() = 0;
};

#endif // CAMERA_HPP
