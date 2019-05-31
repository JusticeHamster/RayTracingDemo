#include "cube.hpp"
#include "ray.hpp"

#include "opengl/opengl_header.hpp"

cube::cube(glm::vec3 axis_x, glm::vec3 axis_y, glm::vec3 axis_z, glm::vec3 extend, glm::vec3 center)
{
    this->axis_x = axis_x;
    this->axis_y = axis_y;
    this->axis_z = axis_z;
    this->extend = extend;
    this->center = center;
    init_vertex();
}

cube::~cube()
{
}

void cube::init_vertex()
{
    vertex[0] = extend * (-axis_x - axis_y + axis_z);
    vertex[1] = extend * (-axis_x + axis_y + axis_z);
    vertex[2] = extend * ( axis_x - axis_y + axis_z);
    vertex[3] = extend * ( axis_x + axis_y + axis_z);
    vertex[4] = extend * ( axis_x - axis_y - axis_z);
    vertex[5] = extend * ( axis_x + axis_y - axis_z);
    vertex[6] = extend * (-axis_x - axis_y - axis_z);
    vertex[7] = extend * (-axis_x + axis_y - axis_z);
    for (int i= 0;i<8;i++){
        vertex[i] /= 2; 
        vertex[i] += center; 
    }
}

glm::vec3 cube::normal(glm::vec3 point) const
{
    return point;
}

void cube::draw(glm::vec3 pos, glm::vec3 di) const
{
    glBegin(GL_QUAD_STRIP); //填充凸多边形
    for (int i= 0;i<8;i++)
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    int t[8] = {0,2,6,4,1,3,7,5};
    for (int i= 0;i<8;i++)
        glVertex3f(vertex[t[i]].x, vertex[t[i]].y, vertex[t[i]].z);
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

float cube::intersect(ray &in) const
{
    return -1;
}
