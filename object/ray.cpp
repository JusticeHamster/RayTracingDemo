#include "ray.hpp"
#include "tools/loader.hpp"

static loader &ldr = loader::instance;

void ray::copy(std::shared_ptr<ray> new_ray) const
{
    line::copy(new_ray);
}

ray::ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, std::reference_wrapper<image> img,
         glm::vec2 image_position, float weight, unsigned time, bool inside):
    line(start, direction, true), rgb(rgb), img(img),
    image_position(image_position), weight(weight), time(time), inside(inside)
{

}

ray::~ray()
{

}

bool ray::is_end() const
{
    return time >= ldr.get_max_scattering_time();
}

glm::vec3 ray::direction() const
{
    return end_point_or_direction();
}

unsigned ray::get_time() const
{
    return time;
}

void ray::stop(glm::vec3 stop_energy)
{
    rgb = stop_energy;
}

image &ray::get_img()
{
    return img;
}

glm::vec2 ray::get_img_position() const
{
    return image_position;
}

void ray::hello() const
{
    qDebug() << "I'm ray";
}

std::shared_ptr<shape> ray::copy() const
{
    auto r = std::make_shared<ray>(start_point(), direction(), rgb, img, image_position, weight, time, inside);
    ray::copy(r);
    return std::shared_ptr<shape>(r);
}

void ray::set_weight(float weight)
{
    this->weight = weight;
}

bool ray::is_inside() const
{
    return inside;
}
