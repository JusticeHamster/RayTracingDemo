#include "cube.hpp"
#include "ray.hpp"
#include "model.hpp"

#include "opengl/opengl_header.hpp"

cube::cube(glm::vec3 axis_x, glm::vec3 axis_y, glm::vec3 axis_z, glm::vec3 extend, glm::vec3 center)
{
    this->axis_x = glm::normalize(axis_x);
    this->axis_y = glm::normalize(axis_y);
    this->axis_z = glm::normalize(axis_z);
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
    vertex[2] = extend * (axis_x - axis_y + axis_z);
    vertex[3] = extend * (axis_x + axis_y + axis_z);
    vertex[4] = extend * (axis_x - axis_y - axis_z);
    vertex[5] = extend * (axis_x + axis_y - axis_z);
    vertex[6] = extend * (-axis_x - axis_y - axis_z);
    vertex[7] = extend * (-axis_x + axis_y - axis_z);
    for (int i = 0; i < 8; i++)
    {
        vertex[i] /= 2;
        vertex[i] += center;
    }
}

glm::vec3 cube::normal(glm::vec3 point) const
{
    return point;
}

void cube::draw() const
{
    init_vertex();
    glm::vec3 pos = get_parent()->get_position();
    glBegin(GL_QUAD_STRIP); //填充凸多边形
    for (int i = 0; i < 8; i++)
        glVertex3f(vertex[i].x+pos.x, vertex[i].y+pos.y, vertex[i].z+pos.z);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    int t[8] = {0, 2, 6, 4, 1, 3, 7, 5};
    for (int i = 0; i < 8; i++)
        glVertex3f(vertex[t[i]].x+pos.x, vertex[t[i]].y+pos.y, vertex[t[i]].z+pos.z);
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

/* 根据平面上一点以及平面的法向量，得到平面方程，并与射线求交点
** point: 平面上的点
** normal: 平面的法向量
** in: 射线
** RETURN: t,点坐标为in.start + t*in.direction(),如果不存在点则返回-1.
*/
float cube::plane(glm::vec3 point, glm::vec3 normal, const ray &in) const
{
    auto t1 = glm::normalize(normal)*in.direction();
    auto ans1 = t1.x+t1.y+t1.z;
    if (ans1>-(1e-5) & ans1<1e-5)
        return -1;
    auto t2 = normal*(in.start_point() - point);
    auto ans2 = t2.x+t2.y+t2.z;
    auto ans = -ans2/ans1;
    return ans<0?-1:ans;
}

/* 传入四个点（构成一个矩形）和一个点，判断点是否在围成点矩形中。
*/
bool cube::point_in_plane() const{
    return true;
}

float cube::intersect(const ray &in) const
{
    float t[6];
    t[0] = plane(vertex[0],axis_z,in);
    t[0] = point_in_plane()?t[0]:-1;
    t[1] = plane(vertex[2],axis_x,in);
    t[1] = point_in_plane()?t[1]:-1;
    t[2] = plane(vertex[4],axis_z,in);
    t[2] = point_in_plane()?t[2]:-1;
    t[3] = plane(vertex[6],axis_x,in);
    t[3] = point_in_plane()?t[3]:-1;
    t[4] = plane(vertex[0],axis_y,in);
    t[4] = point_in_plane()?t[4]:-1;
    t[5] = plane(vertex[1],axis_y,in);
    t[5] = point_in_plane()?t[5]:-1;
    float ans = -1;
    for (int i=0;i<6;i++){
        if (t[i]<0)
            continue;
        ans = ans==-1?t[i]:glm::min(ans,t[i]);
    }
    return ans;
}

void cube::hello() const
{
    qDebug() << "I'm cube";
}

std::shared_ptr<shape> cube::copy() const
{
    std::shared_ptr<shape> c = std::make_shared<cube>(axis_x, axis_y, axis_z, extend, center);
    shape::copy(c);
    return c;
}
