#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <optional>

#include "scene.hpp"

class loader
{
private:
    loader();
public:
    static loader instance;
    scene get_scene(string name);
};

#endif // LOADER_HPP
