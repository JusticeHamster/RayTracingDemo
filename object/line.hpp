#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"
#include "glm/glm.hpp"

class line: public shape
{
private:
    glm::vec3 start, end;
public:
    line(glm::vec3 start, glm::vec3 end);
    virtual ~line();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void draw(glm::vec3 pos, glm::vec3 di) const;
    virtual void rotate();
    virtual void move();
    virtual void scale();
    virtual float intersect(ray &in) const;
    glm::vec3 point(float t);
};

#endif // LINE_HPP
