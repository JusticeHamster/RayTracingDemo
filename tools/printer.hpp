#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "glm/glm.hpp"
#include <string>

class printer
{
public:
    static std::string format(glm::vec3 v);
    static void printf(std::string str);
};

#endif // PRINTER_HPP
