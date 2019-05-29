#include "sphere.hpp"
#include "ray.hpp"

#include <optional>
#include <cstdlib>

#include "glm/glm.hpp"
#include "opengl/opengl_header.hpp"

sphere::sphere(glm::vec3 center, float radius, int m, int n):
    center(center), radius(radius), m(m), n(n)
{

}

sphere::~sphere()
{

}

glm::vec3 sphere::normal(float u, float v)
{
    return glm::vec3(u, v, 0);
}

void sphere::draw(glm::vec3 pos, glm::vec3 di) const
{
    float xx = pos.x + center.x;
    float yy = pos.y + center.y;
    float zz = pos.z + center.z;
    float step_z = PI / m;
    float step_xy = 2 * PI / n;
    float x[4], y[4], z[4];

    float angle_z = 0.0;
    float angle_xy = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for(i = 0; i < m; i++)
    {
        angle_z = i * step_z;

        for(j = 0; j < n; j++)
        {
            angle_xy = j * step_xy;

            x[0] = radius * sin(angle_z) * cos(angle_xy);
            y[0] = radius * sin(angle_z) * sin(angle_xy);
            z[0] = radius * cos(angle_z);

            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radius * cos(angle_z + step_z);

            x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
            y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
            z[2] = radius * cos(angle_z + step_z);

            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radius * cos(angle_z);
            for(int k = 0; k < 4; k++)
            {
                glColor3f(sin(angle_z), cos(angle_z), tan(angle_z));
                glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
            }
        }
    }
    glEnd();
}

void sphere::rotate()
{

}

void sphere::move()
{

}

void sphere::scale()
{

}

float sphere::intersect(ray &in) const
{
    glm::vec3 v1 = glm::normalize(glm::vec3(3, 7, 8)); // 单位化方向向量
    glm::vec3 v2(7-1, 4-2, 5-3); // 空间点方向向量
    float dst = glm::length(glm::cross(v1, v2));
    return -1;
}
