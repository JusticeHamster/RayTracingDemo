#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "base/vertex.hpp"
#include "base/texture.hpp"

class mesh
{
public:
    std::vector<vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<texture> textures;
    mesh(std::vector<vertex> vertices, std::vector<unsigned> indices, std::vector<texture> textures);
    // void draw(shader);
private:
    unsigned VAO, VBO, EBO;
    void setup();
};

#endif // MESH_HPP
