#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "glm/glm.hpp"

#include "object/model.hpp"

class line;

class scene
{
private:
    std::string name;
    std::vector<model> models;
    std::vector<model> lights;
public:
    scene(std::string name);
    void draw();
    glm::vec3 power(line norm) const;
    void push(model m);
    int object_count() const;
};

#endif // SCENE_HPP
