#include "renderer.hpp"

#include <iostream>
#include <chrono>

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
        return;
    }
    //
    render_lock.unlock();
}

void renderer::render(scene &scn)
{
    QtConcurrent::run(this, &renderer::__render, scn);
}
