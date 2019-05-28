#include "intersection.hpp"

intersection::intersection(float t,
    std::shared_ptr<ray_distribution> out,
    glm::vec3 point, glm::vec3 stop_energy
): t(t), out(out), point(point),
    stop_energy(stop_energy)
{
    ;
}

bool intersection::operator()() const
{
    return t > 0;
}
