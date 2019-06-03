#include "model.hpp"
#include "shape.hpp"
#include "ray.hpp"

model::model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position,
    glm::vec3 direction, bool illuminated, glm::vec3 light):
    position(position), direction(direction), illuminated(illuminated), light(light)
{
    shapes.swap(this->shapes);
}

model::~model()
{

}

void model::draw(glm::vec3 pos, glm::vec3 di) const
{
    for (const auto &s : shapes) {
        s->draw(position + pos, direction + di);
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
