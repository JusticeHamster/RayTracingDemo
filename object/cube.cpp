#include "cube.hpp"
#include "ray.hpp"
#include "intersection.hpp"

#include "opengl/opengl_header.hpp"

cube::cube()
{

}

cube::~cube()
{

}

void cube::draw(glm::vec3 pos, glm::vec3 di) const
{
    glBegin(GL_QUAD_STRIP);         //填充凸多边形
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glColor3f(1, 1, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glColor3f(0, 1, 1);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();
}

void cube::rotate()
{

}

void cube::move()
{

}

void cube::scale()
{

}

intersection cube::intersect(ray &in) const
{
    return intersection(false, nullptr, glm::vec3(), glm::vec3());
}
