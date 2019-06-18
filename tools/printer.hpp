#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "glm/glm.hpp"
#include <string>

class printer
{
public:
    static std::string format(glm::vec3 v);
    static std::string format(glm::ivec2 v);
    static std::string format(float f);
    static void print(std::string str);
};

#endif // PRINTER_HPP
