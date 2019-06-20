#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QMutex>
#include <list>
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

    void rays_render(scene &scn, std::list<ray> &rays);
    void __render(scene &scn);

    bool rendering = false;

    glm::uvec2 wh;
public:
    renderer(const renderer &r) = delete;
    renderer(const renderer &&r) = delete;
    renderer();
    void render(scene &scn);
    bool is_rendering() const;
    intersection BRDF(ray &in, const shape &s, glm::vec3 point, const scene &scn) const;

    void set_light_width_height(glm::uvec2 wh);
};

#endif // RENDERER_HPP
