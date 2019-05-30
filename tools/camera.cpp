#include "camera.hpp"

#include "object/cube.hpp"
#include "object/model.hpp"

camera::camera(unsigned width, unsigned height): width(width), height(height)
{

}

camera::~camera()
{

}

model camera::object(glm::vec3 position, glm::vec3 direction) const
{
    auto camera_object = std::make_shared<cube>();
    camera_object->set_blockable(false);
    return model({ camera_object }, position, direction, false, glm::vec3());
}
