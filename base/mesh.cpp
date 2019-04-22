#include "mesh.hpp"

#include "opengl/opengl_header.hpp"

#include <qopenglextrafunctions.h>

using namespace std;

mesh::mesh(vector<vertex> vertices, vector<unsigned> indices, vector<texture> textures):
    vertices(vertices), indices(indices), textures(textures) {
    setup();
}

void mesh::draw(shader s) {
    unsigned diffuseNr = 1;
    unsigned specularNr = 1;
    for (unsigned i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // 0, 1, 2内存连续
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = to_string(specularNr++);
        }
        s.set("material." + name + number, static_cast<float>(i));
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void mesh::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size<vertex>(vertices), ptr(vertices), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<unsigned>(indices), ptr(indices), GL_STATIC_DRAW);

    // Vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void *>(offsetof(vertex, position)));
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void *>(offsetof(vertex, normal)));
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void *>(offsetof(vertex, textureCoords)));
}
