#include "renderer.hpp"

#include <QDebug>

#include "qtconcurrentrun.h"

renderer::renderer(const camera &cmr): cmr(cmr)
{
    ;
}

void renderer::rays_render(std::queue<ray> &rays)
{
    // render all the rays in queue<ray>
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
    rays_render(q_rays);
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
