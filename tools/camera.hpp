#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <memory>

#include "object/ray.hpp"
#include "image.hpp"

class model;

class camera
{
protected:
    camera(unsigned width, unsigned height);
public:
    image img;

    virtual ~camera();
    virtual std::vector<ray> ray_generation() = 0;
    model object(glm::vec3 position, glm::vec3 direction) const;
};

#endif // CAMERA_HPP
