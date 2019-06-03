#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "glm/glm.hpp"

class drawable
{
public:
    virtual ~drawable();
    virtual void draw() const = 0;
};

#endif // DRAWABLE_HPP
