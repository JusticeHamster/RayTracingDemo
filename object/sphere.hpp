#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "glm/glm.hpp"

class sphere: public shape
{
private:
    glm::vec3 center;
    float radius;
    int m, n;
public:
    constexpr static double PI = 3.141592653589793238463;
    sphere(glm::vec3 center, float radius, int m, int n);
    virtual ~sphere();
    glm::vec3 normal(float u, float v);
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual intersection intersect(ray &in) const;
};

#endif // SPHERE_HPP
