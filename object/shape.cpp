#include "shape.hpp"

#include "opengl/opengl_header.hpp"

uint64_t shape::ID = 0;

void shape::copy(std::shared_ptr<shape> new_shape) const
{
    new_shape->set_parent(get_parent());
    new_shape->set_blockable(is_block());
    new_shape->set_transformable(is_transform());
    new_shape->id = id;
    new_shape->need_serialize = need_serialize;
}

shape::~shape()
{

}

glm::vec3 shape::get_rgb() const
{
    // default is (0, 0, 0)
    return {};
}

void shape::set_rgb(glm::vec3 rgb) const
{
    glColor3f(rgb.r, rgb.g, rgb.b);
}

void shape::set_parent(model *parent)
{
    this->parent = parent;
}

model *shape::get_parent() const
{
    return parent;
}

uint64_t shape::get_id() const
{
    return id;
}

buffer shape::_serialize() const
{
    buffer b;
    b.push_back(is_transform());
    b.push_back(is_block());
    b.push_back(is_draw());
    b.push_back(need_serialize);
    buffer t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&id), sizeof(uint64_t));
    b.insert(b.end(), t.begin(), t.end());
    return b;
}

void shape::deserialize(buffer &buf)
{
    ID++;
    serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&id), sizeof(uint64_t));
    need_serialize = buf.back();
    buf.pop_back();
    set_draw(buf.back());
    buf.pop_back();
    set_blockable(buf.back());
    buf.pop_back();
    set_transformable(buf.back());
    buf.pop_back();
}
