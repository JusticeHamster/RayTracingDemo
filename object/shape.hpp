#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"
#include "glm/gtc/constants.hpp"

class shape: public transformable, public blockable, public drawable
{
public:
    constexpr static float PI = glm::pi<float>();
    virtual ~shape();
    virtual glm::vec3 normal(glm::vec3 point) const = 0;
};

#endif // SHAPE_HPP
