#include "loader.hpp"

#include "not_running_exception.hpp"

loader loader::instance;

loader::loader()
{
    ;
}

scene &loader::get_scene(std::string name)
{
    if (scn)
        return *scn;
    QMutexLocker locker(&load_lock);
    if (scn)
        return *scn;
    scn = scene(name);
    return *scn;
}

scene &loader::get_running_scene()
{
    QMutexLocker locker(&load_lock);
    if (!scn) {
        throw not_running_exception("scene not loaded now.");
    }
    return *scn;
}

int loader::get_fps()
{
    return FPS;
}

float loader::get_factor(std::string name)
{
    if (name == "pack")
        return PACK_FACTOR;
    else if (name == "distance")
        return DISTANCE_FACTOR;
    return 0;
}

int loader::get_sampling_number()
{
    return sampling_number;
}

unsigned loader::get_max_scattering_time()
{
    return max_scattering_time;
}

glm::vec3 loader::get_bound(bool upper) const
{
    return upper ? upper_bound : lower_bound;
}
