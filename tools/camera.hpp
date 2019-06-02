#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <memory>
#include <optional>
#include <QMutex>

#include "object/ray.hpp"
#include "object/model.hpp"
#include "image.hpp"

class camera
{
private:
    std::optional<model> obj;

    QMutex object_lock;
protected:
    glm::vec3 position, direction, up;
    camera(unsigned width, unsigned height, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
public:
    image img;

    virtual ~camera();
    virtual std::vector<ray> ray_generation() = 0;
    model object();
};

#endif // CAMERA_HPP
