#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"

class shape: public transformable, public blockable, public drawable
{
public:
    virtual ~shape() {}
};

#endif // SHAPE_HPP
