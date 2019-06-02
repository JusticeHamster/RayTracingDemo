#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "shape.hpp"

class tetrahedron: public shape
{
private:
public:
    tetrahedron();
    virtual ~tetrahedron();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(const ray &in) const;
};

#endif // TETRAHEDRON_HPP
