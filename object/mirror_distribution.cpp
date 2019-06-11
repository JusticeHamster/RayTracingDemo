#include "mirror_distribution.hpp"
#include "ray.hpp"

#include "tools/printer.hpp"

mirror_distribution::~mirror_distribution()
{

}

mirror_distribution::mirror_distribution(ray &parent, glm::vec3 point, glm::vec3 norm,
    float reflection_rate, float refraction_rate, float eta): ray_distribution(parent, point, norm),
    reflection_rate(reflection_rate), refraction_rate(refraction_rate), eta(eta)
{
    if (reflection_rate == 0.f && refraction_rate == 0.f) {
        this->reflection_rate = 1.f;
    } else {
        glm::vec2 norm_rate = glm::normalize(glm::vec2(reflection_rate, refraction_rate));
        this->reflection_rate = norm_rate.x;
        this->refraction_rate = norm_rate.y;
    }
}

// 对镜面反射、折射来说，不需要采样
std::vector<ray> mirror_distribution::random(int num) const
{
    glm::vec3 N = parent.is_inside() ? -norm : norm;
    glm::vec3 L = -parent.direction();
    float NL = glm::dot(N, L);
    float delta = 1 - eta * eta * (1 - NL * NL);
    // 计算反射
    auto reflection_ray = ray(point, parent.direction() + 2.f * N, glm::vec3(), parent.get_img(), parent.get_img_position(), 1, parent.get_time() + 1, parent.is_inside());
    reflection_ray.set_parent(&parent);
    if (reflection_rate == 1.f) {
        parent.add_child(&reflection_ray);
        return { reflection_ray };
    }
    if (reflection_rate == 0.f && delta < 0)
        return {};
    // 计算折射
    glm::vec3 refraction = (eta * NL - glm::sqrt(delta)) * N - eta * L;
    auto refraction_ray = ray(point, refraction, glm::vec3(), parent.get_img(), parent.get_img_position(), 1, parent.get_time() + 1, !parent.is_inside());
    refraction_ray.set_parent(&parent);
    parent.add_child(&refraction_ray);
    if (refraction_rate == 1.f)
        return { refraction_ray };
    parent.add_child(&reflection_ray);
    reflection_ray.set_weight(reflection_rate);
    refraction_ray.set_weight(refraction_rate);
    return { reflection_ray, refraction_ray };
}
