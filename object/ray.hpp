#ifndef RAY_HPP
#define RAY_HPP

#include "glm/glm.hpp"

#include <memory>

#include "line.hpp"

class image;

class ray: public line
{
private:
    glm::vec3 rgb;
    std::reference_wrapper<image> img;
    glm::vec2 image_position;
    double weight;
    unsigned time;
protected:
    void copy(std::shared_ptr<ray> new_ray) const;
public:
    const static unsigned max_scattering_time = 3; // 改为从loader读取配置文件
    ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, std::reference_wrapper<image> img, glm::vec2 image_position, double weight, unsigned time);
    virtual ~ray();
    bool is_end() const;
    glm::vec3 direction() const;
    unsigned get_time() const;
    void stop(glm::vec3 stop_energy);
    image &get_img();
    glm::vec2 get_img_position() const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;
};

#endif // RAY_HPP
