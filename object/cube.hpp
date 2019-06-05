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
    void copy(std::shared_ptr<cube> new_cube) const;

    static std::vector<int> QUAD_ORDER, LINES_ORDER;
public:
    enum style {
        QUAD, LINES
    } draw_style = QUAD;

    cube(glm::vec3 axis_x, glm::vec3 axis_y, glm::vec3 axis_z, glm::vec3 extend, glm::vec3 center);
    virtual ~cube();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw() const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    bool point_in_plane() const;
    virtual float intersect(const ray &in) const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;
};

#endif // CUBE_HPP
