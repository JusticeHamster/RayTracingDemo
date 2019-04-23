#include "vertex.hpp"

using namespace glm;

vertex::vertex() {
    ;
}

vertex::vertex(vec3 position, vec3 normal, vec2 textureCoords, vec3 tangent, vec3 bitangent):
    position(position), normal(normal), textureCoords(textureCoords),
    tangent(tangent), bitangent(bitangent) {
    ;
}
