#include "camera.hpp"

#include "object/cube.hpp"
#include "object/model.hpp"

camera::camera(unsigned width, unsigned height): img(image(width, height))
{

}

camera::~camera()
{

}

model camera::object(glm::vec3 position, glm::vec3 direction) const
{
    auto camera_object = std::make_shared<cube>(
        glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1),
        glm::vec3(1, 1, 1), glm::vec3()
    );
    camera_object->set_blockable(false);
    return model({ camera_object }, position, direction, false, glm::vec3());
}
