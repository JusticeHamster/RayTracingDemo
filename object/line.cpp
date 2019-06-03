#include "line.hpp"
#include "ray.hpp"
#include "model.hpp"

#include "opengl/opengl_header.hpp"

line::line(glm::vec3 start, glm::vec3 direction, bool is_ray): is_ray(is_ray), start(start)
{
    if (is_ray) {
        end = glm::normalize(direction);
    } else {
        end = direction;
    }
}

line::line(glm::vec3 start, glm::vec3 end): line(start, end, false)
{

}

line::~line()
{

}

glm::vec3 line::normal(glm::vec3 point) const
{
    return point;
}

void line::draw() const
{
    glm::vec3 pos = get_parent()->get_position();
    glm::vec3 __end(end);
    if (is_direction()) {
        __end *= t;
        __end += start;
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x0F0F);
    }
    glBegin(GL_LINES);
    glVertex3f(start.x + pos.x, start.y + pos.y, start.z + pos.z);
    glVertex3f(__end.x + pos.x, __end.y + pos.y, __end.z + pos.z);
    glEnd();
    if (is_direction()) {
        glDisable(GL_LINE_STIPPLE);
    }
}

void line::rotate()
{

}

void line::move()
{

}

void line::scale()
{

}

#include <optional>
#include <cstdlib>

inline bool is_equal(float x, float y)
{
  constexpr float epsilon = 1e-5f;
  return std::abs(x - y) <= epsilon * std::abs(x);
}

inline std::optional<float> __t(float left, float right) {
    return is_equal(left, 0) ? std::nullopt : std::optional<float>(right / left);
}

// (1 - t) * s + t * e { 0 <= t <= 1 }
float line::intersect(const ray &in) const
{
    // not implemented
    return -1;
}

glm::vec3 line::start_point() const
{
    return start;
}

bool line::is_direction() const
{
    return is_ray;
}

glm::vec3 line::end_point_or_direction() const
{
    return end;
}

glm::vec3 line::point(float t) const
{
    if (is_ray)
        return start + t * end;
    return start + t * (end - start);
}

void line::set_t(float t)
{
    this->t = t;
}

void line::hello() const
{
    qDebug() << "I'm line";
}
