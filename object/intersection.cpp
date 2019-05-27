#include "intersection.hpp"

intersection::intersection(bool is_intersect,
    ray_distribution &out, vec3 point, vec3 stop_energy
): is_intersect(is_intersect), out(out), point(point),
    stop_energy(stop_energy)
{
    ;
}
