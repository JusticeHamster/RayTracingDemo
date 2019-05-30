#include "blockable.hpp"

blockable::~blockable()
{

}

float blockable::ray_intersect(ray &in) const
{
    if (!block) {
        return -1;
    }
    return intersect(in);
}

void blockable::set_blockable(bool block)
{
    this->block = block;
}
