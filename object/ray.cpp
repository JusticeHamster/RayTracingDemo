#include "ray.hpp"

ray::ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, glm::vec2 image_position,
         double weight, unsigned time): line(start, direction, true),
    rgb(rgb), image_position(image_position), weight(weight), time(time)
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

void ray::intersect_one_time()
{
    time++;
}
