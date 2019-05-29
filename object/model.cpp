#include "model.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "intersection.hpp"

#include <optional>

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

float model::intersect(ray &in) const
{
    std::optional<float> min;
    for (const auto &s : shapes) {
        float t = s->intersect(in);
        if (t > 0 && (!min || t < *min))
            min = t;
    }
    if (min)
        return *min;
    return -1;
}

intersection model::BRDF(ray &in) const
{

}
