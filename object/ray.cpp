#include "ray.hpp"
#include "tools/loader.hpp"
#include "tools/image.hpp"
#include "tools/printer.hpp"

static loader &ldr = loader::instance;

void ray::copy(std::shared_ptr<ray> new_ray) const
{
    line::copy(new_ray);
    new_ray->parent_shape = parent_shape;
    new_ray->parent_ray = parent_ray;
    new_ray->childs = childs;
    if (parent_ray != nullptr)
    {
        unsigned index = 0;
        for (ray *child : parent_ray->childs)
        {
            if (child == this)
                break;
            index++;
        }
        if (index < parent_ray->childs.size())
            parent_ray->childs[index] = new_ray.get();
    }
    for (ray *child : new_ray->childs)
        child->parent_ray = new_ray.get();
}

ray::ray(glm::vec3 start, glm::vec3 direction, glm::vec3 rgb, std::reference_wrapper<image> img,
         glm::uvec2 image_position, float weight, unsigned time, bool inside) : line(start, direction, true), rgb(rgb), img(img),
                                                                                image_position(image_position), weight(weight), time(time), inside(inside)
{
    need_serialize = false;
}

ray::ray(const ray &r) : line(r), rgb(r.rgb), img(r.img),
                         image_position(r.image_position), weight(r.weight), time(r.time), inside(r.inside)
{
    parent_shape = r.parent_shape;
    parent_ray = r.parent_ray;
    childs = r.childs;
    if (parent_ray != nullptr)
    {
        unsigned index = 0;
        for (ray *child : parent_ray->childs)
        {
            if (child == &r)
                break;
            index++;
        }
        if (index < parent_ray->childs.size())
            parent_ray->childs[index] = this;
    }
    for (ray *child : childs)
        child->parent_ray = this;
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
    rgb += stop_energy;
    float w = weight;
    img.get().add(stop_energy * w, image_position.x, image_position.y);
    for (ray *p = parent_ray; p != nullptr; p = p->parent_ray) {
        w /= p->weight;
        p->rgb += stop_energy * w;
    }
}

image &ray::get_img()
{
    return img;
}

glm::uvec2 ray::get_img_position() const
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

void ray::add_child(ray *child)
{
    childs.push_back(child);
}

void ray::set_parent_ray(ray *parent)
{
    parent_ray = parent;
}

static glm::vec3 bound_diff = ldr.get_bound() - ldr.get_bound(false);
static glm::vec3 lower_bound = ldr.get_bound(false);

glm::vec3 ray::get_rgb() const
{
    float t = rgb.x + rgb.y + rgb.z;
    glm::vec3 c1(137.0f / 255, 207.0f / 255, 240.0f / 255);
    glm::vec3 c2(35.0f / 255, 45.0f / 255, 150.0f / 255);
    glm::vec3 c3(154.0f / 255, 255.0f / 255, 154.0f / 255);
    glm::vec3 c4(0.0f / 255, 205.0f / 255, 102.0f / 255);
    glm::vec3 c5(255.0f / 255, 215.0f / 255, 0.0f / 255);
    glm::vec3 c6(205.0f / 255, 149.0f / 255, 12.0f / 255);
    t /= 3.0f;
    if (t < 0.33f)
        return c3 + t * (c4 - c3);
    else if (t > 0.66f)
        return c5 + t * (c6 - c5);
    else
        return c1 + t * (c2 - c1);
}

uint64_t ray::type_id() const
{
    return 2;
}
