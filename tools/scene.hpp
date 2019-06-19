#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <QMutex>

#include "glm/glm.hpp"

#include "object/model.hpp"
#include "object/helloable.hpp"

#include "serializable.hpp"

class line;

class scene: public helloable, public serializable
{
private:
    std::string name;
    std::vector<model> models;
    std::vector<model> lights;

    mutable QMutex lock;
    friend class renderer;
protected:
    virtual buffer _serialize() const;
public:
    scene(std::string name);
    scene(const scene &scn);
    scene(scene &&scn);
    scene &operator=(const scene &scn);
    scene &operator=(scene &&scn);

    void hello() const;
    void draw() const;
    glm::vec3 power(line norm) const;
    void push(model m);
    void pop(int index);
    int object_count() const;

    virtual void deserialize(buffer &buf);
};

#endif // SCENE_HPP
