#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <optional>
#include <QMutex>

#include "scene.hpp"

class loader
{
private:
    loader();
    std::optional<scene> scn;
    constexpr static int FPS = 60;
    constexpr static int sampling_number = 5;
    constexpr static float PACK_FACTOR = .5f;
    constexpr static float DISTANCE_FACTOR = 2.f;
    constexpr static float ROTATE_SPEED = .01f;
    constexpr static float WHEEL_SPEED = .01f;
    constexpr static float PHONE_ANGLE = 15.f;
    constexpr static unsigned max_scattering_time = 3;
    constexpr static glm::vec3 lower_bound = glm::vec3();
    constexpr static glm::vec3 upper_bound = glm::vec3(0.75f);

    QMutex load_lock;
public:
    static loader instance;
    scene &get_scene(std::string name);
    scene &get_running_scene();
    int get_fps();
    float get_factor(std::string name);
    int get_sampling_number();
    unsigned get_max_scattering_time();
    glm::vec3 get_bound(bool upper = true) const;
};

#endif // LOADER_HPP
