#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "glm/glm.hpp"

class drawable
{
protected:
    virtual ~drawable() {}
public:
    virtual void draw(glm::vec3 pos, glm::vec3 di) const = 0;
};

#endif // DRAWABLE_HPP
