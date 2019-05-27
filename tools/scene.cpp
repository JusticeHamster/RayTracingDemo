#include "scene.hpp"

#include "object/sphere.hpp"
#include "object/cube.hpp"
#include "object/tetrahedron.hpp"
#include "object/line.hpp"

scene::scene(string name): name(name)
{
    // 随便放一个场景
    models.push_back(model({
        std::make_shared<sphere>(glm::vec3(), 0.5, 100, 100),
    }, glm::vec3(), glm::vec3(), false, glm::vec3()));

    models.push_back(model({
        std::make_shared<cube>(),
    }, glm::vec3(0, 3, 0), glm::vec3(), false, glm::vec3()));

    models.push_back(model({
        std::make_shared<tetrahedron>(),
        std::make_shared<line>(glm::vec3(), glm::vec3(3, 3, -3)),
    }, glm::vec3(0, -3, 0), glm::vec3(), false, glm::vec3()));
}

void scene::draw()
{
    for (const model &m : models) {
        m.draw(glm::vec3(), glm::vec3());
    }
}
