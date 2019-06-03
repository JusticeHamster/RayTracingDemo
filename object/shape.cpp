#include "shape.hpp"

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
