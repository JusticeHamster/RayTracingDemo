#include "renderer.hpp"

#include <QDebug>
#include "tools/printer.hpp"

#include "qtconcurrentrun.h"

#include "object/intersection.hpp"
#include "object/diffuse_distribution.hpp"
#include "object/mirror_distribution.hpp"
#include "object/phone_distribution.hpp"
#include "tools/pinhole_camera.hpp"
#include "tools/loader.hpp"
#include "tools/not_implemented_exception.hpp"

static loader &ldr = loader::instance;

void renderer::rays_render(scene &scn, std::list<ray> &rays)
{
    auto iray = rays.begin();
    int count = 0;
    while (iray != rays.end()) {
        ray &r = *iray;
        // work through all the models (no acceleration)
        model::intersect_result result(std::nullopt, -1);
        qDebug() << "round:" << ++count;
        for (const model &m : scn.models) {
            auto ir = m.intersect(r);
            auto [optional_reference_shape, t] = ir;
            if (optional_reference_shape) {
                if (!r.is_inside() && r.parent_shape == optional_reference_shape->get().get_id())
                    continue;
                if (!std::get<0>(result) || t < std::get<1>(result))
                    result = ir;
            }
        }
        // generate new rays or stop
        auto [optional_reference_shape, t] = result;
        if (optional_reference_shape) {
            intersection i = BRDF(r, optional_reference_shape->get(), r.point(t), scn);
            if (i) {
                for (ray &_r : i.out->random(ldr.get_sampling_number())) {
                    _r.parent_shape = optional_reference_shape->get().get_id();
                    rays.push_back(_r);
                }
            } else {
                r.stop(i.stop_energy);
            }
        } else {
            qDebug() << "nothing happened.";
        }
        // draw
        auto sr = std::make_shared<ray>(r);
        sr->set_blockable(false);
        sr->need_serialize = false;
        if (optional_reference_shape)
            sr->set_t(t);
        auto m = model({ sr }, glm::vec3(), glm::vec3(), false, glm::vec3());
        m.need_serialize = false;
        scn.push(m);
        // advance
        iray++;
    }
}

void renderer::__render(scene &scn)
{
    rendering = true;
    // add camera object
    scn.push(cmr->object());
    auto rays = cmr->ray_generation();
    std::list<ray> lrays;
    for (const ray &r : rays)
        lrays.push_back(r);
    rays_render(scn, lrays);
    //

    rendering = false;
    render_lock.unlock();
}

renderer::renderer()
{

}

void renderer::render(scene &scn)
{
    // 一个时间只能有一个渲染任务
    if (!render_lock.try_lock()) {
        qDebug() << "rendering...";
        return;
    }
    cmr = std::make_unique<pinhole_camera>(wh.x, wh.y, glm::vec3(-2), glm::vec3(2));
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
    std::shared_ptr<ray_distribution> rd;
    switch (s.get_parent()->distribution_type) {
    case model::diffuse: {
        rd.reset(new diffuse_distribution(in, point, norm));
        break;
    }
    case model::mirror: {
        auto param = s.get_parent()->mirror_param;
        rd.reset(new mirror_distribution(in, point, norm, param.x, param.y, param.z));
        break;
    }
    case model::phone:
        rd.reset(new phone_distribution(in, point, norm, ldr.get_factor("angle") * shape::PI / 180.f));
    }
    return intersection(false, rd, point, {});
}

void renderer::set_light_width_height(glm::uvec2 wh)
{
    this->wh = wh;
}
