#include "shape.hpp"

#include "opengl/opengl_header.hpp"

void shape::copy(std::shared_ptr<shape> new_shape) const
{
    new_shape->set_parent(get_parent());
    new_shape->set_blockable(is_block());
}

shape::~shape()
{

}

glm::vec3 shape::get_rgb() const
{
    // default is (0, 0, 0)
    return {};
}

void shape::set_rgb(glm::vec3 rgb) const
{
    glColor3f(rgb.r, rgb.g, rgb.b);
}

void shape::set_parent(model *parent)
{
    this->parent = parent;
}

model *shape::get_parent() const
{
    return parent;
}
