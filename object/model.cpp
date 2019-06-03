#include "model.hpp"
#include "shape.hpp"
#include "ray.hpp"

model::model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position,
    glm::vec3 direction, bool illuminated, glm::vec3 light):
    position(position), direction(direction), illuminated(illuminated), light(light)
{
    for (const auto &s : shapes)
        s->set_parent(this);
    shapes.swap(this->shapes);
}

model::model(const model &m): shapes(m.shapes), position(m.position), direction(m.direction), illuminated(m.illuminated), light(m.light)
{
    for (const auto &s : shapes)
        s->set_parent(this);
}

model::model(model &&m): position(m.position), direction(m.direction), illuminated(m.illuminated), light(m.light)
{
    shapes.swap(m.shapes);
    for (const auto &s : shapes)
        s->set_parent(this);
}

model &model::operator=(const model &m)
{
    position = m.position;
    direction = m.direction;
    illuminated = m.illuminated;
    light = m.light;
    shapes = m.shapes;
    for (const auto &s : shapes)
        s->set_parent(this);
    return *this;
}

model &model::operator=(model &&m)
{
    position = m.position;
    direction = m.direction;
    illuminated = m.illuminated;
    light = m.light;
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
        s->draw();
    }
}

void model::rotate()
{

}

void model::move()
{

}

void model::scale()
{

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
    std::optional<std::reference_wrapper<const shape> > intersect_shape;
    std::optional<float> min;
    for (const auto &s : shapes) {
        float t = s->ray_intersect(in);
        if (t >= 0 && (!min || t < *min)) {
            min = t;
            intersect_shape = *s;
        }
    }
    return {intersect_shape, min ? *min : 0};
}

void model::hello() const
{
    qDebug() << "I have" << shapes.size() << "shapes:";
    for (const auto &s : shapes) {
        s->hello();
    }
}
