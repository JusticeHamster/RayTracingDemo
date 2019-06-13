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
protected:
    void copy(std::shared_ptr<line> new_line) const;
    virtual void draw() const;
    virtual float intersect(const ray &in) const;
    virtual void apply(glm::mat4 mat);
public:
    line(glm::vec3 start, glm::vec3 direction, bool is_ray);
    line(glm::vec3 start, glm::vec3 end);
    virtual ~line();
    virtual glm::vec3 normal(glm::vec3 point) const;
    glm::vec3 start_point() const;
    glm::vec3 end_point_or_direction() const;
    bool is_direction() const;
    glm::vec3 point(float t) const;
    void set_t(float t);
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;

    virtual buffer serialize() const;
    virtual void deserialize(buffer buf);
};

#endif // LINE_HPP
