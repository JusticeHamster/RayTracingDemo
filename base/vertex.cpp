#include "vertex.hpp"

using namespace glm;

vertex::vertex() {
    ;
}

vertex::vertex(vec3 position, vec3 normal = vec3(), vec2 textureCoords = vec2()):
    position(position), normal(normal), textureCoords(textureCoords) {
    ;
}
