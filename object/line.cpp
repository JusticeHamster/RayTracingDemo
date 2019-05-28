#include "line.hpp"
#include "ray.hpp"

#include "opengl/opengl_header.hpp"

line::line(glm::vec3 start, glm::vec3 end): start(start), end(end)
{

}

line::~line()
{

}

void line::draw(glm::vec3 pos, glm::vec3 di) const
{
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(start.x + pos.x, start.y + pos.y, start.z + pos.z);
    glVertex3f(end.x + pos.x, end.y + pos.y, end.z + pos.z);
    glEnd();
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
float line::intersect(ray &in) const
{
    if (in.is_end()) {
        return -1;
    }
    auto right = start - in.start;
    auto left = right + in.end - end;
    auto t1 = __t(left.x, right.x);
    auto t2 = __t(left.y, right.y);
    auto t3 = __t(left.z, right.z);
    if (t1 == t2 && t2 == t3) {
        if (!t1)
            return -1;
        float t = *t1;
        if (t < 0 || t > 1)
            return -1;
        return t;
    }
    return -1;
}
