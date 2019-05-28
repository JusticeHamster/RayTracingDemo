#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "glm/glm.hpp"

#include <memory>

class ray_distribution;

class intersection
{
private:
    float t;
    std::shared_ptr<ray_distribution> out;
    glm::vec3 point;
    glm::vec3 stop_energy;
public:
    intersection(
        float t, std::shared_ptr<ray_distribution> out,
        glm::vec3 point, glm::vec3 stop_energy
    );
    bool operator()() const;
};

#endif // INTERSECTION_HPP
