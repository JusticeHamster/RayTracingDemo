#include "renderer.hpp"

#include <QDebug>

#include "qtconcurrentrun.h"

#include "object/intersection.hpp"
#include "object/diffuse_distribution.hpp"
#include "object/mirror_distribution.hpp"

renderer::renderer(const camera &cmr): cmr(cmr)
{
    ;
}

void renderer::rays_render(const scene &scn, std::queue<ray> &rays)
{
    while (!rays.empty()) {
        ray &r = rays.front();
        model::intersect_result result(std::nullopt, -1);
        // work through all the models (no acceleration)
        for (const model &m : scn.models) {
            auto ir = m.intersect(r);
            auto [optional_reference_shape, t] = ir;
            if (optional_reference_shape) {
                if (!std::get<0>(result) || std::get<1>(result) < t)
                    result = ir;
            }
        }
        auto [optional_reference_shape, t] = result;
        if (optional_reference_shape) {
            intersection i = BRDF(r, optional_reference_shape->get(), r.point(t), scn);
            if (i) {
                ;
            } else {
                i.stop_energy;
            }
        }
        r.intersect_one_time();
        rays.pop();
    }
}

void renderer::__render(scene &scn)
{
    rendering = true;
    // add camera object
    glm::vec3 position(2, 2, 2);
    int index = scn.object_count();
    scn.push(cmr.object(position, -position));
    auto rays = cmr.ray_generation();
    std::queue<ray> q_rays;
    for (auto &ray : rays)
        q_rays.push(std::move(ray));
    rays_render(scn, q_rays);
    scn.pop(index);
    //
    rendering = false;
    render_lock.unlock();
}

void renderer::render(scene &scn)
{
    // 一个时间只能有一个渲染任务
    if (!render_lock.try_lock()) {
        qDebug() << "rendering...";
        return;
    }
    QtConcurrent::run(this, &renderer::__render, std::ref(scn));
}

bool renderer::is_rendering() const
{
    return rendering;
}

intersection renderer::BRDF(const ray &in, const shape &s, glm::vec3 point, const scene &scn) const
{
    glm::vec3 norm = s.normal(point);
    if (in.is_end()) {
        return intersection(true, nullptr, point, scn.power(line(point, norm, true)));
    }
    // 根据配置的表面信息选择ray_distribution
    std::shared_ptr<ray_distribution> rd(new diffuse_distribution());
    return intersection(false, rd, point, {});
}
