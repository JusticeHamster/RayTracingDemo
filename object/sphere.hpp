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
    glm::vec3 normal(float u, float v);
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(ray &in) const;
};

#endif // SPHERE_HPP
