#include "tetrahedron.hpp"
#include "ray.hpp"
#include "model.hpp"

#include "opengl/opengl_header.hpp"

tetrahedron::tetrahedron()
{

}

tetrahedron::~tetrahedron()
{

}

glm::vec3 tetrahedron::normal(glm::vec3 point) const
{
    return point;
}

void tetrahedron::draw() const
{
    glm::vec3 pos = get_parent()->get_position();

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

float tetrahedron::intersect(const ray &in) const
{
    return -1;
}
