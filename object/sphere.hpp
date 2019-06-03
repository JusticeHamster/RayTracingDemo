#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "glm/glm.hpp"

#include "shape.hpp"

class sphere: public shape
{
private:
    glm::vec3 center;
    float radius;
    int m, n;
public:
    sphere(glm::vec3 center, float radius, int m, int n);
    virtual ~sphere();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw() const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(const ray &in) const;
};

#endif // SPHERE_HPP
