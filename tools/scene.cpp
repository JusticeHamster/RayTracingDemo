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
    }, glm::vec3(.5, -.5, 0), glm::vec3(), false, glm::vec3(), model::mirror);
    m.mirror_param = glm::vec3(1., 0., 1.33);
    m.set_name("ball_1");
    // m.set_draw(false);
    push(m);

    // 放一个方块
    m = model({
        std::make_shared<cube>(glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1), glm::vec3()),
    }, glm::vec3(-.5, -2, -1.2), glm::vec3(), true, glm::vec3(1), model::diffuse);
    m.set_name("cube_1");
    push(m);

    // 另一个球
    m = model({
        std::make_shared<sphere>(glm::vec3(), 1.5, 30, 30)
    }, glm::vec3(3), glm::vec3(), false, glm::vec3(), model::diffuse);
    m.set_name("ball_2");
    push(m);

    // 另一个方块
    m = model({
        std::make_shared<cube>(glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0), glm::vec3(0, 0, 1), glm::vec3(2), glm::vec3()),
    }, glm::vec3(-3, 2, 0), glm::vec3(), false, glm::vec3(), model::phone);
    m.mirror_param = glm::vec3(1., 0., 1.33);
    m.set_name("cube_2");
    push(m);

    // 坐标轴
    auto x = std::make_shared<line>(glm::vec3(), glm::vec3(-10, 0, 0));
    auto y = std::make_shared<line>(glm::vec3(), glm::vec3(0, 10, 0));
    auto z = std::make_shared<line>(glm::vec3(), glm::vec3(0, 0, -10));
    x->set_blockable(false);
    y->set_blockable(false);
    z->set_blockable(false);
    m = model({ x, y, z }, glm::vec3(), glm::vec3(), false, glm::vec3());
    m.set_name("axis");
    push(m);
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

model &scene::get_model(int index)
{
    return models.at(static_cast<uint64_t>(index));
}

const model &scene::get_model(int index) const
{
    return models.at(static_cast<uint64_t>(index));
}

void scene::remove_model(model *m)
{
    QMutexLocker locker(&lock);
    auto it = models.begin();
    for (const auto &model : models) {
        if (m == &model)
            break;
        it++;
    }
    models.erase(it);
}

buffer scene::_serialize() const
{
    QMutexLocker locker(&lock);
    buffer b;
    buffer t = serializable::serialize(name);
    b.insert(b.end(), t.begin(), t.end());
    int size = 0;
    for (const auto &m : models) {
        t = m.serialize();
        if (t.size() == 0 || m.object_count() == 0) {
            continue;
        }
        size++;
        b.insert(b.end(), t.begin(), t.end());
    }
    t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&size), sizeof(int));
    b.insert(b.end(), t.begin(), t.end());
    size = 0;
    for (const auto &l : lights) {
        t = l.serialize();
        if (l.object_count() == 0) {
            continue;
        }
        size++;
        b.insert(b.end(), t.begin(), t.end());
    }
    t = serializable::serialize(reinterpret_cast<const buffer_value_type *>(&size), sizeof(int));
    b.insert(b.end(), t.begin(), t.end());
    return b;
}

void scene::deserialize(buffer &buf)
{
    QMutexLocker locker(&lock);
    int size;
    serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&size), sizeof(int));
    lights.clear();
    lights.resize(static_cast<uint64_t>(size));
    for (auto it = lights.rbegin(); it != lights.rend(); ++it) {
        it->deserialize(buf);
    }
    serializable::deserialize(buf, reinterpret_cast<buffer_value_type *>(&size), sizeof(int));
    models.clear();
    models.resize(static_cast<uint64_t>(size));
    for (auto it = models.rbegin(); it != models.rend(); ++it) {
        it->deserialize(buf);
    }
    serializable::deserialize(buf, name);
}
