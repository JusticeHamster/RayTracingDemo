#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"
#include "glm/glm.hpp"

class line: public shape
{
private:
    bool is_ray;
    float t = 10;
    glm::vec3 start, end;
public:
    line(glm::vec3 start, glm::vec3 direction, bool is_ray);
    line(glm::vec3 start, glm::vec3 end);
    virtual ~line();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(const ray &in) const;
    glm::vec3 start_point() const;
    glm::vec3 end_point_or_direction() const;
    bool is_direction() const;
    glm::vec3 point(float t) const;
    void set_t(float t);
};

#endif // LINE_HPP
