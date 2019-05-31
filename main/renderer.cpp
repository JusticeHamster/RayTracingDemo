#include "renderer.hpp"

#include <chrono>
#include <QDebug>

#include "qtconcurrentrun.h"

renderer::renderer(const camera &cmr): cmr(cmr)
{
    ;
}

using namespace std::chrono_literals;

void renderer::__render(scene &scn)
{
    // 一个时间只能有一个渲染任务
    if (!render_lock.try_lock()) {
        qDebug() << "rendering...";
        return;
    }
    // add camera object
    glm::vec3 position(2, 2, 2);
    int index = scn.object_count();
    scn.push(cmr.object(position, -position));
    std::this_thread::sleep_for(10s);
    scn.pop(index);
    //
    render_lock.unlock();
}

void renderer::render(scene &scn)
{
    QtConcurrent::run(this, &renderer::__render, std::ref(scn));
}
