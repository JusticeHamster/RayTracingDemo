#include "renderer.hpp"

#include <QDebug>
#include "tools/printer.hpp"

#include "qtconcurrentrun.h"

#include "object/intersection.hpp"
#include "object/diffuse_distribution.hpp"
#include "object/mirror_distribution.hpp"
#include "tools/pinhole_camera.hpp"
#include "tools/loader.hpp"
#include "tools/not_implemented_exception.hpp"

static loader &ldr = loader::instance;

void renderer::rays_render(scene &scn, std::list<ray> &rays)
{
    auto iray = rays.begin();
    int count = 1;
    while (iray != rays.end()) {
        ray &r = *iray;
        // work through all the models (no acceleration)
        model::intersect_result result(std::nullopt, -1);
        qDebug() << "round:" << count++;
        for (const model &m : scn.models) {
            auto ir = m.intersect(r);
            auto [optional_reference_shape, t] = ir;
            if (optional_reference_shape) {
                if (!std::get<0>(result) || t < std::get<1>(result))
                    result = ir;
            }
        }
        // generate new rays or stop
        auto [optional_reference_shape, t] = result;
        if (optional_reference_shape) {
            printer::print(r.point(t));
            intersection i = BRDF(r, optional_reference_shape->get(), r.point(t), scn);
            if (i) {
                for (const ray &r : i.out->random(ldr.get_sampling_number()))
                    rays.push_back(r);
            } else {
                r.stop(i.stop_energy);
            }
        } else {
            qDebug() << "nothing happened.";
        }
        // draw
        auto sr = std::make_shared<ray>(r);
        sr->set_blockable(false);
        if (optional_reference_shape)
            sr->set_t(t);
        scn.push(model({ sr }, glm::vec3(), glm::vec3(), false, glm::vec3()));
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
    cmr = std::make_unique<pinhole_camera>(1, 1, glm::vec3(-2), glm::vec3(2));
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
        throw new not_implemented_exception("phone高光暂时没实现");
    }
    return intersection(false, rd, point, {});
}
