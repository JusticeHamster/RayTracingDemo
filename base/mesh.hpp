#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "base/vertex.hpp"
#include "base/texture.hpp"
#include "base/shader.hpp"

class mesh
{
public:
    std::vector<vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<texture> textures;
    mesh(std::vector<vertex> vertices, std::vector<unsigned> indices, std::vector<texture> textures);
    void draw(shader s);
private:
    unsigned VAO, VBO, EBO;
    void setup();
    template<class T> inline long size(std::vector<T> v) { return static_cast<long>(sizeof(v) * v.size()); }
    template<class T> inline void *ptr(std::vector<T> v) { return &v[0]; }
};

#endif // MESH_HPP
