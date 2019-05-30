#include "model.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "tools/loader.hpp"

model::model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position,
    glm::vec3 direction, bool illuminated, glm::vec3 light): ldr(loader::instance),
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

model::intersect_result model::intersect(ray &in) const
{
    std::optional<std::reference_wrapper<const shape> > intersect_shape;
    std::optional<float> min;
    for (const auto &s : shapes) {
        float t = s->intersect(in);
        if (t > 0 && (!min || t < *min)) {
            min = t;
            intersect_shape = *s;
        }
    }
    return {intersect_shape, min ? *min : 0};
}

intersection model::BRDF(ray &in, intersect_result ir) const
{
    auto [optional_shape_reference, t] = ir;
    if (!optional_shape_reference)
        return intersection(true, nullptr, glm::vec3(), glm::vec3());
    const shape &s = optional_shape_reference->get();
    glm::vec3 norm = s.normal(in.point(t));
    if (in.is_end()) {
        // 计算光照
        return intersection(true, nullptr, glm::vec3(), glm::vec3());
    } else {
        ;
    }
}
