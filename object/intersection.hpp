#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "glm/glm.hpp"

#include <memory>

class ray_distribution;

class intersection
{
private:
    bool is_intersect;
    std::shared_ptr<ray_distribution> out;
    glm::vec3 point;
    glm::vec3 stop_energy;
public:
    intersection(
        bool is_intersect, std::shared_ptr<ray_distribution> out,
        glm::vec3 point, glm::vec3 stop_energy
    );
};

#endif // INTERSECTION_HPP
