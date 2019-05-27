#ifndef BLOCKABLE_HPP
#define BLOCKABLE_HPP

#include "intersection.hpp"

class ray;

class blockable
{
protected:
    virtual ~blockable() {}
public:
    virtual intersection intersect(ray &in) const = 0;
};

#endif // BLOCKABLE_HPP
