#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"

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
};

#endif // MESH_HPP
