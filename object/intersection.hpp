#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "glm/glm.hpp"

#include <memory>

class ray_distribution;

class intersection
{
private:
    bool stop;
public:
    std::shared_ptr<ray_distribution> out;
    glm::vec3 point;
    glm::vec3 stop_energy;

    intersection(
        bool stop, std::shared_ptr<ray_distribution> out,
        glm::vec3 point, glm::vec3 stop_energy
    );

    operator bool() const;
};

#endif // INTERSECTION_HPP
