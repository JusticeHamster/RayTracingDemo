#include "loader.hpp"

#include "not_running_exception.hpp"

loader loader::instance;

loader::loader()
{
    ;
}

scene &loader::get_scene(std::string name)
{
    QMutexLocker locker(&lock);
    if (scn)
        return *scn;
    // 加载场景
    scn = scene(name);
    return *scn;
}

scene &loader::get_running_scene()
{
    if (!scn) {
        throw not_running_exception("scene not loaded now.");
    }
    return *scn;
}

int loader::get_fps() const
{
    return FPS;
}
