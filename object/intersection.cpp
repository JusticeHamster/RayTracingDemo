#include "intersection.hpp"

intersection::intersection(bool is_intersect,
    std::shared_ptr<ray_distribution> out,
    glm::vec3 point, glm::vec3 stop_energy
): is_intersect(is_intersect), out(out), point(point),
    stop_energy(stop_energy)
{
    ;
}

bool intersection::operator()() const
{
    return is_intersect;
}
