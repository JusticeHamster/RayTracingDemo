#include "line.hpp"
#include "ray.hpp"
#include "model.hpp"

#include "opengl/opengl_header.hpp"

void line::copy(std::shared_ptr<line> new_line) const
{
    shape::copy(new_line);
    new_line->set_t(t);
}

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

line::line(buffer &buf)
{
    deserialize(buf);
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
    set_rgb(get_rgb());
    glm::vec3 pos(get_parent()->get_position());
    glm::vec3 __start(start + pos);
    glm::vec3 __end(end);
    if (is_direction()) {
        __end *= t;
        __end += __start;
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x0F0F);
        glLineWidth(3);
    } else {
        __end += pos;
    }
    glBegin(GL_LINES);
    glVertex3f(__start.x, __start.y, __start.z);
    glVertex3f(__end.x, __end.y, __end.z);
    glEnd();
    if (is_direction()) {
        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1);
    }
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

void line::apply(glm::mat4 mat)
{

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

std::shared_ptr<shape> line::copy() const
{
    auto l = std::make_shared<line>(start, end, is_ray);
    line::copy(l);
    return std::shared_ptr<shape>(l);
}

uint64_t line::type_id() const
{
    return 1;
}

buffer line::_serialize() const
{
    buffer b = shape::serialize();
    b.push_back(is_ray);
    buffer t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&this->t), sizeof(float));
    b.insert(b.end(), t.begin(), t.end());
    t = serializable::serialize(start);
    b.insert(b.end(), t.begin(), t.end());
    t = serializable::serialize(end);
    b.insert(b.end(), t.begin(), t.end());
    return b;
}

line::line()
{

}

void line::deserialize(buffer &buf)
{
    serializable::deserialize(buf, end);
    serializable::deserialize(buf, start);
    serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&this->t), sizeof(float));
    is_ray = buf.back();
    buf.pop_back();
    shape::deserialize(buf);
}
