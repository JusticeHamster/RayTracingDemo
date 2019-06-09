#include "printer.hpp"

#include <iostream>

void printer::print(glm::vec3 v)
{
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
