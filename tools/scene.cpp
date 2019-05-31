#include "scene.hpp"

#include "object/sphere.hpp"
#include "object/cube.hpp"
#include "object/tetrahedron.hpp"
#include "object/line.hpp"
#include "object/model.hpp"

#include <QDebug>

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

scene::scene(const scene &scn)
{
    *this = scn;
}

scene::scene(scene &&scn)
{
    *this = scn;
}

scene &scene::operator=(const scene &scn)
{
    name = scn.name;
    models = scn.models;
    lights = scn.lights;
    return *this;
}

scene &scene::operator=(scene &&scn)
{
    name.swap(scn.name);
    models.swap(scn.models);
    lights.swap(scn.lights);
    return *this;
}

void scene::hello() const
{
    qDebug() << "scene" << ('<' + name + '>').c_str() << "loaded.";
}

void scene::draw() const
{
    if (!lock.try_lock())
        return;
    for (const model &m : models) {
        m.draw(glm::vec3(), glm::vec3());
    }
    lock.unlock();
}

glm::vec3 scene::power(line norm) const
{
    return {};
}

void scene::push(model m)
{
    QMutexLocker locker(&lock);
    models.push_back(m);
    if (m.is_light()) {
        lights.push_back(m);
    }
}

void scene::pop(int index)
{
    QMutexLocker locker(&lock);
    if (index < 0 || index >= static_cast<int>(models.size()))
        return;
    models.erase(models.begin() + index);
}

int scene::object_count() const
{
    return static_cast<int>(models.size());
}
