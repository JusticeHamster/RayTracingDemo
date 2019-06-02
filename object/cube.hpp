#ifndef CUBE_HPP
#define CUBE_HPP

#include "shape.hpp"

class cube : public shape
{
private:
    glm::vec3 axis_x, axis_y, axis_z, extend, center;
    glm::vec3 vertex[8];
    void init_vertex();
    float plane(glm::vec3 point, glm::vec3 normal, const ray &in) const;
    bool point_in_plane() const;

public:
    cube(glm::vec3 axis_x, glm::vec3 axis_y, glm::vec3 axis_z, glm::vec3 extend, glm::vec3 center);
    virtual ~cube();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(const ray &in) const;
};

#endif // CUBE_HPP
