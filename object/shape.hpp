#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"

class shape: public transformable, public blockable, public drawable
{
public:
    constexpr static float PI = 3.141592653589793238463f;
    virtual ~shape();
};

#endif // SHAPE_HPP
