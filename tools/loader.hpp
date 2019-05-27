#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <optional>
#include <QMutex>

#include "scene.hpp"

class loader
{
private:
    loader();
    optional<scene> scn;

    QMutex lock;
public:
    static loader instance;
    scene &get_scene(string name);
};

#endif // LOADER_HPP
