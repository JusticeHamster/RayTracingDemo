#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "glm/glm.hpp"

class vertex
{
public:
    vertex();
    vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 textureCoords);
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoords;
};

#endif // VERTEX_HPP
