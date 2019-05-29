#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>

class ray;

class camera
{
protected:
    unsigned width, height;
    camera(unsigned width, unsigned height);
public:
    virtual ~camera();
    virtual std::vector<ray> ray_generation() = 0;
};

#endif // CAMERA_HPP
