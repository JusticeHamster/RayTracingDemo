#include "mesh.hpp"

mesh::mesh(std::vector<vertex> vertices, std::vector<unsigned> indices, std::vector<texture> textures):
    vertices(vertices), indices(indices), textures(textures) {
    setup();
}

void mesh::setup() {
    ;
}
