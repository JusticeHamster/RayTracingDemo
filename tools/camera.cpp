#include "camera.hpp"

#include <QMutexLocker>

#include "object/cube.hpp"

camera::camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up):
    position(position), direction(direction), up(up), img(image(width, height))
{
    // recalculate vectors
    direction = glm::normalize(direction);
    left = glm::normalize(glm::cross(up, direction));
    up = glm::normalize(glm::cross(direction, left));
}

camera::~camera()
{

}

model camera::object()
{
    if (obj)
        return *obj;
    QMutexLocker locker(&object_lock);
    if (obj)
        return *obj;
    auto camera_object = std::make_shared<cube>(
        glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1),
        glm::vec3(.3, .3, .3), glm::vec3()
    );
    camera_object->draw_style = cube::LINES;
    camera_object->set_blockable(false);
    camera_object->need_serialize = false;
    obj = model({ camera_object }, position, direction, false, glm::vec3());
    obj->need_serialize = false;
    return *obj;
}
