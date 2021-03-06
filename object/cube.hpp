#ifndef CUBE_HPP
#define CUBE_HPP

#include "shape.hpp"

class cube : public shape
{
private:
    glm::vec3 axis_x, axis_y, axis_z, extend, center;
    glm::vec3 vertex[8];
    glm::mat4 T; //世界坐标系*T = cube坐标系
    void init_vertex();
    void init_T();
    float plane(glm::vec3 point, glm::vec3 normal, const ray &in) const;
    void copy(std::shared_ptr<cube> new_cube) const;
    static std::vector<int> QUAD_ORDER, LINES_ORDER;
protected:
    virtual void draw() const;
    virtual float intersect(const ray &in) const;
    virtual void apply(glm::mat4 mat);

    virtual buffer _serialize() const;
public:
    enum style {
        QUAD, LINES
    } draw_style = QUAD;

    cube(glm::vec3 axis_x, glm::vec3 axis_y, glm::vec3 axis_z, glm::vec3 extend, glm::vec3 center);
    cube(buffer &buf);
    virtual ~cube();
    virtual glm::vec3 normal(glm::vec3 point) const;
    bool point_in_plane(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 x) const;
    glm::vec3 get_extend() const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;
    virtual void set_parent(model *parent);

    virtual uint64_t type_id() const;
    virtual void deserialize(buffer &buf);
};

#endif // CUBE_HPP
