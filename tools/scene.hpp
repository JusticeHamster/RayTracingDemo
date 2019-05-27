#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "object/model.hpp"

class scene
{
private:
    std::string name;
    std::vector<model> models;
    std::vector<model> lights;
public:
    scene(std::string name);
    void draw();
};

#endif // SCENE_HPP
