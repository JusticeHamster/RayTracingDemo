#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"
#include "helloable.hpp"
#include "glm/gtc/constants.hpp"

class model;

class shape: public transformable, public blockable, public drawable, public helloable
{
private:
    model *parent = nullptr;
public:
    constexpr static float PI = glm::pi<float>();
    virtual ~shape();
    virtual glm::vec3 normal(glm::vec3 point) const = 0;
    void set_parent(model *parent);
    model *get_parent() const;
};

#endif // SHAPE_HPP
