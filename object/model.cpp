#include "model.hpp"
#include "shape.hpp"
#include "ray.hpp"

uint64_t model::ID = 0;

model::model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position,
    glm::vec3 direction, bool illuminated, glm::vec3 light, distribution dist): id(++ID),
    position(position), direction(direction), illuminated(illuminated), light(light),
    distribution_type(dist)
{
    for (const auto &s : shapes)
        s->set_parent(this);
    this->shapes.swap(shapes);
}

model::model(const model &m): id(m.id), position(m.position), direction(m.direction),
    illuminated(m.illuminated), light(m.light), distribution_type(m.distribution_type),
    mirror_param(m.mirror_param)
{
    ID++;
    set_draw(m.is_draw());
    for (const auto &s : m.shapes) {
        auto new_shape = s->copy();
        new_shape->set_parent(this);
        shapes.push_back(new_shape);
    }
}

model::model(model &&m): id(m.id), position(m.position), direction(m.direction),
    illuminated(m.illuminated), light(m.light), distribution_type(m.distribution_type),
    mirror_param(m.mirror_param)
{
    ID++;
    set_draw(m.is_draw());
    shapes.swap(m.shapes);
    for (const auto &s : shapes)
        s->set_parent(this);
}

model::model()
{

}

model::model(buffer &buf)
{
    deserialize(buf);
}

model &model::operator=(const model &m)
{
    ID++;
    id = m.id;
    position = m.position;
    direction = m.direction;
    illuminated = m.illuminated;
    light = m.light;
    distribution_type = m.distribution_type;
    mirror_param = m.mirror_param;
    set_draw(m.is_draw());
    for (const auto &s : shapes) {
        auto new_shape = s->copy();
        new_shape->set_parent(this);
        this->shapes.push_back(new_shape);
    }
    return *this;
}

model &model::operator=(model &&m)
{
    ID++;
    id = m.id;
    position = m.position;
    direction = m.direction;
    illuminated = m.illuminated;
    light = m.light;
    distribution_type = m.distribution_type;
    mirror_param = m.mirror_param;
    set_draw(m.is_draw());
    shapes.swap(m.shapes);
    for (const auto &s : shapes)
        s->set_parent(this);
    return *this;
}

model::~model()
{

}

void model::draw() const
{
    for (const auto &s : shapes) {
        s->draw_object();
    }
}

void model::apply(glm::mat4 mat)
{
    for (const auto &s : shapes) {
        s->transform(mat);
    }
}

bool model::is_light() const
{
    return illuminated;
}

glm::vec3 model::get_light() const
{
    return light;
}

glm::vec3 model::get_position() const
{
    return position;
}

glm::vec3 model::get_direction() const
{
    return direction;
}

model::intersect_result model::intersect(const ray &in) const
{
    std::optional<std::reference_wrapper<shape> > intersect_shape;
    std::optional<float> min;
    for (const auto &s : shapes) {
        float t = s->ray_intersect(in);
        if (t > 0 && (!min || t < *min)) {
            min = t;
            intersect_shape = *s;
        }
    }
    return {intersect_shape, min ? *min : 0};
}

void model::hello() const
{
    auto count = static_cast<unsigned>(shapes.size());
    const char *s = count <= 1 ? "shape:" : "shapes:";
    qDebug() << "I have" << count << s;
    for (const auto &s : shapes) {
        s->hello();
    }
}

uint64_t model::get_id() const
{
    return id;
}

int model::object_count() const
{
    return static_cast<int>(shapes.size());
}

buffer model::_serialize() const
{
    buffer b;
    b.push_back(is_draw());
    b.push_back(is_transform());
    buffer t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&id), sizeof(uint64_t));
    b.insert(b.end(), t.begin(), t.end());
    int size = 0;
    for (auto shape : shapes) {
        t = shape->serialize();
        if (t.size() == 0) {
            continue;
        }
        size += t.size();
        b.insert(b.end(), t.begin(), t.end());
        auto tid = shape->type_id();
        t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&tid), sizeof(uint64_t));
        b.insert(b.end(), t.begin(), t.end());
    }
    t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&size), sizeof(int));
    b.insert(b.end(), t.begin(), t.end());
    t = serializable::serialize(position);
    b.insert(b.end(), t.begin(), t.end());
    t = serializable::serialize(direction);
    b.insert(b.end(), t.begin(), t.end());
    b.push_back(illuminated);
    t = serializable::serialize(light);
    b.insert(b.end(), t.begin(), t.end());
    b.push_back(static_cast<buffer_value_type>(distribution_type));
    t = serializable::serialize(mirror_param);
    b.insert(b.end(), t.begin(), t.end());
    return b;
}

#include "cube.hpp"
#include "line.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "tetrahedron.hpp"

void model::deserialize(buffer &buf)
{
    serializable::deserialize(buf, mirror_param);
    switch(buf.back()) {
    case 0: distribution_type = diffuse; break;
    case 1: distribution_type = mirror; break;
    case 2: distribution_type = phone; break;
    }
    buf.pop_back();
    serializable::deserialize(buf, light);
    illuminated = buf.back();
    buf.pop_back();
    serializable::deserialize(buf, direction);
    serializable::deserialize(buf, position);
    int size;
    serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&size), sizeof(int));
    shapes.resize(static_cast<uint64_t>(size));
    for (auto it = shapes.rbegin(); it != shapes.rend(); it++) {
        ID++;
        uint64_t tid;
        serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&tid), sizeof(uint64_t));
        std::shared_ptr<shape> s;
        switch(tid) {
        case 0:
            s = std::make_shared<cube>(buf);
            break;
        case 1:
            s = std::make_shared<line>(buf);
            break;
        case 3:
            s = std::make_shared<sphere>(buf);
            break;
        case 4:
            s = std::make_shared<tetrahedron>(buf);
            break;
        default:
            break;
        }
        if (s) {
            s->set_parent(this);
            *it = s;
        }
    }
    serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&id), sizeof(uint64_t));
    set_transformable(buf.back());
    buf.pop_back();
    set_draw(buf.back());
    buf.pop_back();
}
