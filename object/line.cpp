#include "line.hpp"

#include "opengl/opengl_header.hpp"

line::line(glm::vec3 start, glm::vec3 end): start(start), end(end)
{

}

line::~line()
{

}

void line::draw(glm::vec3 pos, glm::vec3 di) const
{
    glBegin(GL_LINES);
    glVertex3f(start.x + pos.x, start.y + pos.y, start.z + pos.z);
    glVertex3f(end.x + pos.x, end.y + pos.y, end.z + pos.z);
    glEnd();
}

void line::rotate()
{

}

void line::move()
{

}

void line::scale()
{

}

intersection line::intersect(ray &in) const
{
    return intersection(false, nullptr, glm::vec3(), glm::vec3());
}
