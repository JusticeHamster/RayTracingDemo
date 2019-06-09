#include "cube.hpp"
#include "ray.hpp"
#include "model.hpp"

#include "opengl/opengl_header.hpp"
#include "tools/not_implemented_exception.hpp"
#include <glm/gtc/type_ptr.hpp>

cube::cube(glm::vec3 axis_x, glm::vec3 axis_y, glm::vec3 axis_z, glm::vec3 extend, glm::vec3 center)
{
    this->axis_x = glm::normalize(axis_x);
    this->axis_y = glm::normalize(axis_y);
    this->axis_z = glm::normalize(axis_z);
    this->extend = extend;
    this->center = center;
    init_vertex();
    init_T();
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

void cube::init_T()
{
    // 计算转换矩阵
    float a[16] = {-1.f, -1.f, 1.f, 1.f,
                   -1.f, 1.f, -1.f, -1.f,
                   1.f, 1.f, 1.f, -1.f,
                   1.f, 1.f, 1.f, 1.f};
    glm::mat4 A = glm::make_mat4(a);
    float b[16] = {vertex[0].x, vertex[1].x, vertex[2].x, vertex[4].x,
                   vertex[0].y, vertex[1].y, vertex[2].y, vertex[4].y,
                   vertex[0].z, vertex[1].z, vertex[2].z, vertex[4].z,
                   1.f, 1.f, 1.f, 1.f};
    glm::mat4 B = glm::make_mat4(b);
    T = glm::inverse(A) * B;
}

glm::vec3 cube::normal(glm::vec3 point) const
{
    if (point_in_plane(vertex[0], vertex[1], vertex[3], vertex[2], point))
        return axis_z;
    else if (point_in_plane(vertex[2], vertex[3], vertex[5], vertex[4], point))
        return axis_x;
    else if (point_in_plane(vertex[4], vertex[5], vertex[7], vertex[6], point))
        return axis_z;
    else if (point_in_plane(vertex[0], vertex[1], vertex[7], vertex[6], point))
        return axis_x;
    else if (point_in_plane(vertex[0], vertex[2], vertex[4], vertex[6], point))
        return axis_y;
    else if (point_in_plane(vertex[1], vertex[3], vertex[5], vertex[7], point))
        return axis_y;
    throw new not_implemented_exception("error side");
}

std::vector<int> cube::QUAD_ORDER = {0, 2, 6, 4, 1, 3, 7, 5};
std::vector<int> cube::LINES_ORDER = {0, 1, 2, 3, 4, 5, 6, 7, 0, 2, 1, 3, 4, 6, 5, 7, 0, 6, 1, 7, 2, 4, 3, 5};

void cube::draw() const
{
    glm::vec3 pos = get_parent()->get_position();
    if (draw_style == style::QUAD)
    {
        glColor3f(.28f, .46f, 1.f); // 染色
        glBegin(GL_QUAD_STRIP);     //填充凸多边形
        for (int i = 0; i < 8; i++)
        {
            glVertex3f(vertex[i].x + pos.x, vertex[i].y + pos.y, vertex[i].z + pos.z);
        }
        glEnd();
        glBegin(GL_QUAD_STRIP);
        for (unsigned long i = 0; i < QUAD_ORDER.size(); i++)
        {
            glVertex3f(vertex[QUAD_ORDER[i]].x + pos.x, vertex[QUAD_ORDER[i]].y + pos.y, vertex[QUAD_ORDER[i]].z + pos.z);
        }
        glEnd();
    }
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for (unsigned long i = 0; i < LINES_ORDER.size(); i++)
    {
        glVertex3f(vertex[LINES_ORDER[i]].x + pos.x, vertex[LINES_ORDER[i]].y + pos.y, vertex[LINES_ORDER[i]].z + pos.z);
    }
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
    auto t1 = glm::normalize(normal) * in.direction();
    auto ans1 = t1.x + t1.y + t1.z;
    if (ans1 > -(1e-5) & ans1 < 1e-5)
        return -1;
    auto t2 = normal * (in.start_point() - point);
    auto ans2 = t2.x + t2.y + t2.z;
    auto ans = -ans2 / ans1;
    return ans < 0 ? -1 : ans;
}

/* 传入四个点abcd（构成一个矩形）和一个点x，判断点是否在围成点矩形中。
    点坐标均为世界坐标系
*/
bool cube::point_in_plane(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 x) const
{
    glm::vec4 ta(a.x, a.y, a.z, 1.0f);
    glm::vec4 tb(b.x, b.y, b.z, 1.0f);
    glm::vec4 tc(c.x, c.y, c.z, 1.0f);
    glm::vec4 td(d.x, d.y, d.z, 1.0f);
    glm::vec4 tx(x.x, x.y, x.z, 1.0f);
    ta = ta * T;
    tb = tb * T;
    tc = tc * T;
    td = td * T;
    tx = tx * T;
    a = glm::vec3(ta);
    b = glm::vec3(tb);
    c = glm::vec3(tc);
    d = glm::vec3(td);
    x = glm::vec3(tx);
    if (glm::abs(x.x-a.x)<=1e-5 &&glm::abs(b.x-a.x)<=1e-5 && glm::abs(c.x-a.x)<=1e-5 && glm::abs(d.x-a.x)<=1e-5)
    {
        auto min_y = glm::min(glm::min(a.y, b.y), glm::min(c.y, d.y));
        auto min_z = glm::min(glm::min(a.z, b.z), glm::min(c.z, d.z));
        auto max_y = glm::max(glm::max(a.y, b.y), glm::max(c.y, d.y));
        auto max_z = glm::max(glm::max(a.z, b.z), glm::max(c.z, d.z));
        return x.y >= min_y && x.y <= max_y && x.z >= min_z && x.z <= max_z;
    }
    else if (glm::abs(x.y-a.y)<=1e-5 &&glm::abs(b.y-a.y)<=1e-5 && glm::abs(c.y-a.y)<=1e-5 && glm::abs(d.y-a.y)<=1e-5)
    {
        auto min_x = glm::min(glm::min(a.x, b.x), glm::min(c.x, d.x));
        auto min_z = glm::min(glm::min(a.z, b.z), glm::min(c.z, d.z));
        auto max_x = glm::max(glm::max(a.x, b.x), glm::max(c.x, d.x));
        auto max_z = glm::max(glm::max(a.z, b.z), glm::max(c.z, d.z));
        return x.x >= min_x && x.x <= max_x && x.z >= min_z && x.z <= max_z;
    }
    else if (glm::abs(x.z-a.z)<=1e-5 &&glm::abs(b.z-a.z)<=1e-5 && glm::abs(c.z-a.z)<=1e-5 && glm::abs(d.z-a.z)<=1e-5)
    {
        auto min_y = glm::min(glm::min(a.y, b.y), glm::min(c.y, d.y));
        auto min_x = glm::min(glm::min(a.x, b.x), glm::min(c.x, d.x));
        auto max_y = glm::max(glm::max(a.y, b.y), glm::max(c.y, d.y));
        auto max_x = glm::max(glm::max(a.x, b.x), glm::max(c.x, d.x));
        return x.y >= min_y && x.y <= max_y && x.x >= min_x && x.x <= max_x;
    }
    else
        return false;
}

void cube::copy(std::shared_ptr<cube> new_cube) const
{
    shape::copy(new_cube);
    new_cube->draw_style = draw_style;
}

float cube::intersect(const ray &in) const
{
    float t[6];
    t[0] = plane(vertex[0], axis_z, in);
    t[0] = point_in_plane(vertex[0], vertex[1], vertex[3], vertex[2], in.point(t[0])) ? t[0] : -1;
    t[1] = plane(vertex[2], axis_x, in);
    t[1] = point_in_plane(vertex[2], vertex[3], vertex[5], vertex[4], in.point(t[1])) ? t[1] : -1;
    t[2] = plane(vertex[4], axis_z, in);
    t[2] = point_in_plane(vertex[4], vertex[5], vertex[7], vertex[6], in.point(t[2])) ? t[2] : -1;
    t[3] = plane(vertex[6], axis_x, in);
    t[3] = point_in_plane(vertex[0], vertex[1], vertex[7], vertex[6], in.point(t[3])) ? t[3] : -1;
    t[4] = plane(vertex[0], axis_y, in);
    t[4] = point_in_plane(vertex[0], vertex[2], vertex[4], vertex[6], in.point(t[4])) ? t[4] : -1;
    t[5] = plane(vertex[1], axis_y, in);
    t[5] = point_in_plane(vertex[1], vertex[3], vertex[5], vertex[7], in.point(t[5])) ? t[5] : -1;
    float ans = -1;
    for (int i = 0; i < 6; i++)
    {
        if (t[i] < 0)
            continue;
        ans = ans < 0 ? t[i] : glm::min(ans, t[i]);
    }
    return ans;
}

void cube::hello() const
{
    qDebug() << "I'm cube";
}

std::shared_ptr<shape> cube::copy() const
{
    std::shared_ptr<cube> c = std::make_shared<cube>(axis_x, axis_y, axis_z, extend, center);
    cube::copy(c);
    return std::shared_ptr<shape>(c);
}
