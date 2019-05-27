#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"
#include "glm/glm.hpp"

using namespace glm;

class line: public shape
{
private:
    vec3 start, end, normal;
public:
    line();
};

#endif // LINE_HPP
