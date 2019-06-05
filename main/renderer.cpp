#include "renderer.hpp"

#include <QDebug>

#include "qtconcurrentrun.h"

#include "object/intersection.hpp"
#include "object/diffuse_distribution.hpp"
#include "object/mirror_distribution.hpp"
#include "tools/pinhole_camera.hpp"
#include "tools/loader.hpp"

loader &ldr = loader::instance;

void renderer::rays_render(scene &scn, std::queue<ray> &rays)
{
    int count = 1;
    while (!rays.empty()) {
        ray &r = rays.front();
        // work through all the models (no acceleration)
        model::intersect_result result(std::nullopt, -1);
        qDebug() << "round:" << count++;
        for (const model &m : scn.models) {
            auto ir = m.intersect(r);
            auto [optional_reference_shape, t] = ir;
            if (optional_reference_shape) {
                m.hello();
                qDebug() << t;
                if (!std::get<0>(result) || std::get<1>(result) < t)
                    result = ir;
            }
        }
        // generate new Rays or stop
        auto [optional_reference_shape, t] = result;
        auto l = std::make_shared<line>(r);
        l->set_blockable(false);
        if (optional_reference_shape) {
            l->set_t(t);
            intersection i = BRDF(r, optional_reference_shape->get(), r.point(t), scn);
            if (i) {
                for (const ray &r : i.out->random(ldr.get_sampling_number()))
                    rays.push(r);
            } else {
                r.stop(i.stop_energy);
            }
        } else {
            qDebug() << "nothing happened.";
        }
        // draw
        scn.push(model({ l }, glm::vec3(), glm::vec3(), false, glm::vec3()));
        // pop
        rays.pop();
    }
}

void renderer::__render(scene &scn)
{
    rendering = true;
    // add camera object
    scn.push(cmr->object());
    auto rays = cmr->ray_generation();
    std::queue<ray> q_rays;
    for (const ray &r : rays)
        q_rays.push(r);
    rays_render(scn, q_rays);
    //

    rendering = false;
    render_lock.unlock();
}

renderer::renderer()
{
    cmr = std::make_unique<pinhole_camera>(2, 1, glm::vec3(-2), glm::vec3(2));
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

intersection renderer::BRDF(ray &in, const shape &s, glm::vec3 point, const scene &scn) const
{
    glm::vec3 norm = s.normal(point);
    if (s.get_parent()->is_light()) {
        return intersection(true, nullptr, point, s.get_parent()->get_light());
    }
    if (in.is_end()) {
        return intersection(true, nullptr, point, scn.power(line(point, norm, true)));
    }
    // 根据配置的表面信息选择ray_distribution
    std::shared_ptr<ray_distribution> rd(new mirror_distribution(in, point, norm, .1f, .0f, .5f));
    return intersection(false, rd, point, {});
}
