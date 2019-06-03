#include "sphere.hpp"
#include "ray.hpp"
#include "model.hpp"

#include <optional>

#include "glm/glm.hpp"
#include "opengl/opengl_header.hpp"

sphere::sphere(glm::vec3 center, float radius, int m, int n) : center(center), radius(radius), m(m), n(n)
{
}

sphere::~sphere()
{
}

glm::vec3 sphere::normal(glm::vec3 point) const
{
    return glm::normalize(point - center);
}

void sphere::draw() const
{
    glm::vec3 pos = get_parent()->get_position();
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
    for (i = 0; i < m; i++)
    {
        angle_z = i * step_z;

        for (j = 0; j < n; j++)
        {
            angle_xy = j * step_xy;

            x[0] = radius * glm::sin(angle_z) * glm::cos(angle_xy);
            y[0] = radius * glm::sin(angle_z) * glm::sin(angle_xy);
            z[0] = radius * glm::cos(angle_z);

            x[1] = radius * glm::sin(angle_z + step_z) * glm::cos(angle_xy);
            y[1] = radius * glm::sin(angle_z + step_z) * glm::sin(angle_xy);
            z[1] = radius * glm::cos(angle_z + step_z);

            x[2] = radius * glm::sin(angle_z + step_z) * glm::cos(angle_xy + step_xy);
            y[2] = radius * glm::sin(angle_z + step_z) * glm::sin(angle_xy + step_xy);
            z[2] = radius * glm::cos(angle_z + step_z);

            x[3] = radius * glm::sin(angle_z) * glm::cos(angle_xy + step_xy);
            y[3] = radius * glm::sin(angle_z) * glm::sin(angle_xy + step_xy);
            z[3] = radius * glm::cos(angle_z);
            for (int k = 0; k < 4; k++)
            {
                glColor3f(glm::sin(angle_z), glm::cos(angle_z), glm::tan(angle_z));
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

float sphere::intersect(const ray &in) const
{
    glm::vec3 dect = glm::normalize(in.direction());
    auto t = dect * dect;
    auto a = t.x + t.y + t.z;
    t = (in.start_point() - center) * in.direction();
    auto b = 2 * (t.x + t.y + t.z);
    t = in.start_point() - center;
    t *= t;
    auto c = t.x + t.y + t.z - radius * radius;
    auto delt = b * b - 4 * a * c;
    if (delt < 0)
        return -1;
    else
    {
        auto t1 = -b / 2 / a + glm::sqrt(delt);
        auto t2 = -b / 2 / a - glm::sqrt(delt);
        if (t1*t2<0)
            return glm::max(t1,t2);
        else if (t1*t2==0)
            return 0;
        else if (t1<0 & t2<0)
            return -1;
        else
            return glm::min(t1,t2);
        
    }
}
