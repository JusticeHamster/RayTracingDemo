#include "loader.hpp"

#include "scene.hpp"

using namespace std;

loader loader::instance;

loader::loader()
{
    ;
}

scene &loader::get_scene(string name)
{
    QMutexLocker locker(&lock);
    if (scn)
        return *scn;
    // 加载场景
    scn = scene(name);
    return *scn;
}
