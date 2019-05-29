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
    std::optional<scene> scn;

    QMutex lock;
public:
    static loader instance;
    scene &get_scene(std::string name);
    scene &get_running_scene();
};

#endif // LOADER_HPP
