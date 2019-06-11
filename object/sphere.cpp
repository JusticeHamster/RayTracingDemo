#include "sphere.hpp"
#include "ray.hpp"
#include "model.hpp"

#include <optional>

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "opengl/opengl_header.hpp"

void sphere::copy(std::shared_ptr<sphere> new_sphere) const
{
    shape::copy(new_sphere);
}

sphere::sphere(glm::vec3 center, float radius, int m, int n) : center(center), radius(radius), m(m), n(n)
{
}

sphere::~sphere()
{
}

glm::vec3 sphere::normal(glm::vec3 point) const
{
    return glm::normalize(point - center - get_parent()->get_position());
}

void sphere::draw() const
{
    glm::vec3 _center = center + get_parent()->get_position();
    float step_z = PI / m;
    float step_xy = 2 * PI / n;
    float x[4], y[4], z[4];

    float angle_z = 0.0;
    float angle_xy = 0.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < m; i++)
    {
        angle_z = i * step_z;

        for (int j = 0; j < n; j++)
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
                glVertex3f(_center.x + x[k], _center.y + y[k], _center.z + z[k]);
            }
        }
    }
    glColor3f(0, 0, 0);
    glEnd();
}

float sphere::intersect(const ray &in) const
{
    glm::vec3 _center = center + get_parent()->get_position();
    glm::vec3 dect = glm::normalize(in.direction());
    auto t = dect * dect;
    auto a = t.x + t.y + t.z;
    t = (in.start_point() - _center) * in.direction();
    auto b = 2 * (t.x + t.y + t.z);
    t = in.start_point() - _center;
    t *= t;
    auto c = t.x + t.y + t.z - radius * radius;
    auto delt = b * b - 4 * a * c;
    if (delt < 0)
        return -1;
    else
    {
        auto t1 = -b / (2 * a) + glm::sqrt(delt)/ (2 * a);
        auto t2 = -b / (2 * a) - glm::sqrt(delt)/ (2 * a);
        if (t1*t2 <= 0) {
            auto t = glm::max(t1, t2);
            if (t < 1e-5f)
                return -1;
            return t;
        }
        else if (t1 < 0 && t2 < 0)
            return -1;
        else {
            auto t = glm::min(t1, t2);
            if (t < 1e-5f)
                return -1;
            return t;
        }
    }
}

void sphere::apply(glm::mat4 mat)
{
    glm::vec4 t1(center, 0);
    glm::vec4 t2 = t1;
    t2.x += radius;
    t1 = t1*mat;
    t2 = t2*mat;
    center = t1;
    glm::vec4 t = t2-t1;
    t *= t;
    radius = glm::sqrt(t.x + t.y + t.z);

}

void sphere::hello() const
{
    qDebug() << "I'm sphere";
}

std::shared_ptr<shape> sphere::copy() const
{
    auto s = std::make_shared<sphere>(center, radius, m, n);
    sphere::copy(s);
    return std::shared_ptr<shape>(s);
}

bool sphere::inside(glm::vec3 point) const
{
    return radius * radius >= glm::distance2(point, center + get_parent()->get_position());
}
