#ifndef CUBE_HPP
#define CUBE_HPP

#include "shape.hpp"

class cube: public shape
{
private:
public:
    cube();
    virtual ~cube();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(ray &in) const;
};

#endif // CUBE_HPP
