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
    glm::uvec2 image_position;
    float weight;
    unsigned time;
    bool inside;
    std::vector<ray *> childs;
protected:
    void copy(std::shared_ptr<ray> new_ray) const;
public:
    ray *parent_ray = nullptr;
    ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, std::reference_wrapper<image> img, glm::uvec2 image_position, float weight, unsigned time, bool inside = false);
    ray(const ray &r);
    virtual ~ray();
    bool is_end() const;
    glm::vec3 direction() const;
    unsigned get_time() const;
    void stop(glm::vec3 stop_energy);
    image &get_img();
    glm::uvec2 get_img_position() const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;
    void set_weight(float weight);
    bool is_inside() const;
    void add_child(ray *child);
    void set_parent(ray *parent);
    virtual glm::vec3 get_rgb() const;
};

#endif // RAY_HPP
