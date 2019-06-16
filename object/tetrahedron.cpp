#include "tetrahedron.hpp"
#include "ray.hpp"
#include "model.hpp"

#include "opengl/opengl_header.hpp"

void tetrahedron::copy(std::shared_ptr<tetrahedron> new_tetrahedron) const
{
    shape::copy(new_tetrahedron);
}

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

float tetrahedron::intersect(const ray &in) const
{
    return -1;
}

void tetrahedron::apply(glm::mat4 mat)
{

}

void tetrahedron::hello() const
{
    qDebug() << "I'm tetrahedron";
}

std::shared_ptr<shape> tetrahedron::copy() const
{
    auto t = std::make_shared<tetrahedron>();
    tetrahedron::copy(t);
    return std::shared_ptr<shape>(t);
}

buffer tetrahedron::_serialize() const
{
    return {};
}

void tetrahedron::deserialize(buffer buf)
{

}
