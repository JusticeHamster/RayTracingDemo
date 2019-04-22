#include "vertex.hpp"

using namespace glm;

vertex::vertex() {
    ;
}

vertex::vertex(vec3 position, vec3 normal, vec2 textureCoords):
    position(position), normal(normal), textureCoords(textureCoords) {
    ;
}
