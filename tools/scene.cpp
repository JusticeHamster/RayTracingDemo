#include "scene.hpp"

#include "object/sphere.hpp"
#include "object/cube.hpp"
#include "object/tetrahedron.hpp"
#include "object/line.hpp"
#include "object/model.hpp"

#include <QDebug>

scene::scene(std::string name): name(name)
{
    // 放一个球
    auto m = model({
        std::make_shared<sphere>(glm::vec3(), 1, 30, 30)
    }, glm::vec3(0, -.3, 0), glm::vec3(), false, glm::vec3(), model::mirror);
    m.mirror_param = glm::vec3(0., 1., 1.33);
    //m.set_draw(false);
    push(m);

    // 放一个方块
    push(model({
        std::make_shared<cube>(glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1), glm::vec3()),
    }, glm::vec3(1, 2, 1), glm::vec3(), true, glm::vec3(1), model::diffuse));
    // 另一个球
    push(model({
        std::make_shared<sphere>(glm::vec3(), 1, 30, 30)
    }, glm::vec3(3), glm::vec3(), false, glm::vec3(), model::diffuse));

    // 坐标轴
    auto x = std::make_shared<line>(glm::vec3(), glm::vec3(-10, 0, 0));
    auto y = std::make_shared<line>(glm::vec3(), glm::vec3(0, 10, 0));
    auto z = std::make_shared<line>(glm::vec3(), glm::vec3(0, 0, -10));
    x->set_blockable(false);
    y->set_blockable(false);
    z->set_blockable(false);
    push(model({ x, y, z }, glm::vec3(), glm::vec3(), false, glm::vec3()));
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
        m.draw_object();
    }
    lock.unlock();
}

glm::vec3 scene::power(line norm) const
{
    glm::vec3 light_power;
    for (const model &light : lights) {
        float factor = glm::dot(norm.end_point_or_direction(), glm::normalize(light.get_position() - norm.start_point()));
        light_power += light.get_light() * factor;
    }
    return light_power;
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

buffer scene::_serialize() const
{
    return {};
}

void scene::deserialize(buffer buf)
{

}
