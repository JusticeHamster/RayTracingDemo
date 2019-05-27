#include "model.hpp"

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

intersection model::intersect(ray &in) const
{
    return intersection(false, nullptr, glm::vec3(), glm::vec3());
}
