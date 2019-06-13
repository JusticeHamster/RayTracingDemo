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
