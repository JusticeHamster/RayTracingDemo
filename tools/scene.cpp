#include "scene.hpp"

#include "object/sphere.hpp"
#include "object/cube.hpp"
#include "object/tetrahedron.hpp"
#include "object/line.hpp"
#include "object/model.hpp"

scene::scene(std::string name): name(name)
{
    // 随便放一个场景
    push(model({
        std::make_shared<sphere>(glm::vec3(), 0.5, 100, 100),
    }, glm::vec3(), glm::vec3(), false, glm::vec3()));

    push(model({
        std::make_shared<tetrahedron>(),
    }, glm::vec3(0, 3, 0), glm::vec3(), false, glm::vec3()));

    push(model({
        std::make_shared<line>(glm::vec3(), glm::vec3(3, 3, -3)),
    }, glm::vec3(0, -3, 0), glm::vec3(), false, glm::vec3()));
}

void scene::draw()
{
    for (const model &m : models) {
        m.draw(glm::vec3(), glm::vec3());
    }
}

glm::vec3 scene::power(line norm) const
{
    return {};
}

void scene::push(model m)
{
    models.push_back(m);
    if (m.is_light()) {
        lights.push_back(m);
    }
}

int scene::object_count() const
{
    return models.size();
}
