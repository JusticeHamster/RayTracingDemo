#include "printer.hpp"

#include <QDebug>
#include <sstream>

static std::stringstream ss;

std::string printer::format(glm::vec3 v)
{
    std::stringstream().swap(ss);
    ss << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return ss.str();
}

void printer::printf(std::string str)
{
    qDebug("%s", str.c_str());
}
