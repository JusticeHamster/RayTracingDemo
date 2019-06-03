#include "shape.hpp"

void shape::copy(std::shared_ptr<shape> new_shape) const
{
    new_shape->set_parent(get_parent());
    new_shape->set_blockable(is_block());
}

shape::~shape()
{

}

void shape::set_parent(model *parent)
{
    this->parent = parent;
}

model *shape::get_parent() const
{
    return parent;
}
