#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QMutex>
#include <optional>
#include <queue>

#include "tools/image.hpp"
#include "tools/scene.hpp"
#include "tools/camera.hpp"

class renderer
{
private:
    const camera &cmr;

    QMutex render_lock;

    void __render(std::queue<ray> rays);
    void __render(scene &scn);

    image result;
public:
    renderer(const renderer &r) = delete;
    renderer(const renderer &&r) = delete;
    renderer(const camera &cmr);
    void render(scene &scn);
};

#endif // RENDERER_HPP
