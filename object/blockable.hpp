#ifndef BLOCKABLE_HPP
#define BLOCKABLE_HPP

#include "intersection.hpp"

class ray;

class blockable
{
public:
    virtual intersection intersect(ray &in) = 0;
};

#endif // BLOCKABLE_HPP
