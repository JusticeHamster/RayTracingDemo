#include "ray.hpp"

ray::ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, std::reference_wrapper<image> img,
         glm::vec2 image_position, double weight, unsigned time):
    line(start, direction, true), rgb(rgb), img(img),
    image_position(image_position), weight(weight), time(time)
{

}

ray::~ray()
{

}

bool ray::is_end() const
{
    return time >= max_scattering_time;
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
