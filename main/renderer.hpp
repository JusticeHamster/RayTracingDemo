#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QMutex>
#include <optional>
#include <queue>

#include "tools/image.hpp"
#include "tools/scene.hpp"
#include "tools/camera.hpp"

class intersection;

class renderer
{
private:
    const camera &cmr;

    QMutex render_lock;

    void rays_render(const scene &scn, std::queue<ray> &rays);
    void __render(scene &scn);

    image result;
    bool rendering = false;
public:
    renderer(const renderer &r) = delete;
    renderer(const renderer &&r) = delete;
    renderer(const camera &cmr);
    void render(scene &scn);
    bool is_rendering() const;
    intersection BRDF(const ray &in, const shape &s, glm::vec3 point, const scene &scn) const;
};

#endif // RENDERER_HPP
