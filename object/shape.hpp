#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"

class shape: public transformable, public blockable, public drawable
{

};

#endif // SHAPE_HPP
