#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QMutex>
#include <optional>

#include "tools/image.hpp"
#include "tools/scene.hpp"
#include "tools/camera.hpp"

using namespace std;

class renderer
{
private:
    const camera &cmr;

    QMutex render_lock;

    void __render(scene &scn);
    void __render();

    image result;
public:
    renderer(const renderer &r) = delete;
    renderer(const renderer &&r) = delete;
    renderer(const camera &cmr);
    void render(scene &scn);
};

#endif // RENDERER_HPP
