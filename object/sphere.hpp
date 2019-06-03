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
protected:
    void copy(std::shared_ptr<sphere> new_sphere) const;
public:
    sphere(glm::vec3 center, float radius, int m, int n);
    virtual ~sphere();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw() const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(const ray &in) const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;
};

#endif // SPHERE_HPP
