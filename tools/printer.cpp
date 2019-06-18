#include "printer.hpp"

#include <QDebug>
#include <sstream>
#include <string>

static std::stringstream ss;

std::string printer::format(glm::vec3 v)
{
    std::stringstream().swap(ss);
    ss << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return ss.str();
}

std::string printer::format(glm::ivec2 v)
{
    std::stringstream().swap(ss);
    ss << "(" << v.x << ", " << v.y << ")";
    return ss.str();
}

std::string printer::format(float f)
{
    return std::to_string(f);
}

void printer::print(std::string str)
{
    qDebug("%s", str.c_str());
}
