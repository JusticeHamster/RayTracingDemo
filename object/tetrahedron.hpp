#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "shape.hpp"

class tetrahedron: public shape
{
private:
public:
    tetrahedron();
    virtual ~tetrahedron();
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(ray &in) const;
};

#endif // TETRAHEDRON_HPP
