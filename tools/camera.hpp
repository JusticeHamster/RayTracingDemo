#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>

#include "object/ray.hpp"

class model;

class camera
{
protected:
    unsigned width, height;
    camera(unsigned width, unsigned height);
public:
    virtual ~camera();
    virtual std::vector<ray> ray_generation() const = 0;
    model object(glm::vec3 position, glm::vec3 direction) const;
};

#endif // CAMERA_HPP
