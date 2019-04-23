#include "mesh.hpp"

#include "opengl_header.hpp"

#include <qopenglextrafunctions.h>

using namespace std;

template<class T> inline long size(std::vector<T> v) {
    return static_cast<long>(sizeof(v) * v.size());
}

template<class T> inline void *ptr(std::vector<T> v) {
    return &v[0];
}

mesh::mesh(vector<vertex> vertices, vector<unsigned> indices, vector<texture> textures):
    vertices(vertices), indices(indices), textures(textures) {
    setup();
}

#include <map>

void mesh::draw(shader s) {
    map<string, int> mesh_type = {
        {"texture_diffuse" , 1},
        {"texture_specular", 1},
        {"texture_normal"  , 1},
        {"texture_height"  , 1},
    };
    for (unsigned i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // 0, 1, 2内存连续
        string name = textures[i].type;
        auto type = mesh_type.find(name);
        if (type == mesh_type.end()) continue;
        string number = to_string(type->second++);
        s.set(name + number, static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

#define offset(E) reinterpret_cast<void *>(offsetof(vertex, E))

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), offset(position));
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), offset(normal));
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), offset(textureCoords));
    // Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), offset(tangent));
    // BiTangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), offset(bitangent));

    glBindVertexArray(0);
}

#undef offset
