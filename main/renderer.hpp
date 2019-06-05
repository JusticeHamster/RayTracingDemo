#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QMutex>
#include <queue>
#include <memory>

#include "tools/image.hpp"
#include "tools/scene.hpp"
#include "tools/camera.hpp"

class intersection;

class renderer
{
private:
    std::unique_ptr<camera> cmr;

    QMutex render_lock;

    void rays_render(scene &scn, std::queue<ray> &rays);
    void __render(scene &scn);

    bool rendering = false;
public:
    constexpr static int sampling_number = 10;
    renderer(const renderer &r) = delete;
    renderer(const renderer &&r) = delete;
    renderer();
    void render(scene &scn);
    bool is_rendering() const;
    intersection BRDF(ray &in, const shape &s, glm::vec3 point, const scene &scn) const;
};

#endif // RENDERER_HPP
