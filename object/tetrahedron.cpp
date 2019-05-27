#include "tetrahedron.hpp"

#include "opengl/opengl_header.hpp"

tetrahedron::tetrahedron()
{

}

tetrahedron::~tetrahedron()
{

}

void tetrahedron::draw(glm::vec3 pos, glm::vec3 di) const
{
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1, -1, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1, 1, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(1, -1, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0.7f);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0.7f);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0.7f);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0.7f);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1, 1, 0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 1.2f);
    glEnd();
}

void tetrahedron::rotate()
{

}

void tetrahedron::move()
{

}

void tetrahedron::scale()
{

}

intersection tetrahedron::intersect(ray &in) const
{
    return intersection(false, nullptr, glm::vec3(), glm::vec3());
}
