#include "phone_distribution.hpp"

#include "ray.hpp"
#include "glm/gtc/matrix_transform.hpp"

inline glm::vec2 phone_distribution::generate(float r) const
{
    glm::vec2 value;
    constexpr int try_time = 3;
    for (int i = 0; i < try_time; i++) {
        value = glm::vec2(normal(generator), normal(generator));
        float sl = glm::dot(value, value);
        if (sl <= r * r)
            break;
        else if (i == try_time - 1)
            value = glm::normalize(value) * r;
    }
    return value;
}

glm::vec3 phone_distribution::random_direction(glm::vec3 main, float limit) const
{
    float r = glm::tan(limit), R = glm::sqrt(1 + r * r);
    auto uv = generate(r);
    auto y = glm::sqrt(R * R - glm::dot(uv, uv));
    glm::vec3 d = glm::normalize(glm::vec3(uv.x, y, uv.y));
    glm::vec3 up(0, 1, 0);
    glm::mat4 ro(1.f);
    return glm::vec4(main, 0) * glm::rotate(ro, glm::acos(glm::dot(up, d)), glm::cross(up, d));
}

phone_distribution::~phone_distribution()
{

}

static std::random_device random_device;

phone_distribution::phone_distribution(ray &parent, glm::vec3 point, glm::vec3 norm, float angle_bound):
    ray_distribution(parent, point, norm), generator(random_device()), angle_bound(angle_bound)
{

}

std::vector<ray> phone_distribution::random(int num) const
{
    auto main_direction = glm::normalize(parent.direction() + 2.f * norm);
    auto main_ray = ray(point, main_direction, glm::vec3(), parent.get_img(), parent.get_img_position(), 1.f, parent.get_time() + 1, parent.is_inside());
    if (num == 1)
        return { main_ray };
    main_ray.set_weight(.5f);
    num--;
    if (parent.is_inside())
        return {};
    float limit = shape::PI_2 - glm::acos(glm::dot(norm, main_direction));
    if (angle_bound < limit)
        limit = angle_bound;
    // 2\sigma: 95.450%
    normal = std::normal_distribution<float>(0, limit / 2.f);
    float weight = .5f / num;

    std::vector<ray> rays;
    rays.push_back(main_ray);
    for (int i = 0; i < num; i++) {
        auto rd = random_direction(main_direction, limit);
        auto r = ray(point, rd, glm::vec3(), parent.get_img(), parent.get_img_position(), weight, parent.get_time() + 1, parent.is_inside());
        r.set_parent_ray(&parent);
        parent.add_child(&r);
        rays.push_back(r);
    }
    return rays;
}
