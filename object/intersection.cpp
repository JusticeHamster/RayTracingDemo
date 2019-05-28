#include "intersection.hpp"

intersection::intersection(bool stop,
    std::shared_ptr<ray_distribution> out,
    glm::vec3 point, glm::vec3 stop_energy
): stop(stop), out(out), point(point),
    stop_energy(stop_energy)
{
    ;
}

bool intersection::operator()() const
{
    return stop;
}
