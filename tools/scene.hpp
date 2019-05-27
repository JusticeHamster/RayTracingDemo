#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "object/model.hpp"

using namespace std;

class scene
{
private:
    string name;
    vector<model> models;
    vector<model> lights;
public:
    scene(string name);
    void draw();
};

#endif // SCENE_HPP
