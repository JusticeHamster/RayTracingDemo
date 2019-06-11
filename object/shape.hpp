#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"
#include "helloable.hpp"
#include "glm/gtc/constants.hpp"

#include <memory>

class model;

class shape: public transformable, public blockable, public drawable, public helloable
{
private:
    static uint64_t ID;
    uint64_t id = ++ID;
    model *parent = nullptr;
protected:
    void copy(std::shared_ptr<shape> new_shape) const;
public:
    constexpr static float PI = glm::pi<float>();
    constexpr static float PI2 = PI * 2;
    constexpr static float PI_2 = PI / 2;
    virtual ~shape();
    virtual glm::vec3 normal(glm::vec3 point) const = 0;
    virtual std::shared_ptr<shape> copy() const = 0;
    virtual glm::vec3 get_rgb() const;
    void set_rgb(glm::vec3 rgb) const;
    void set_parent(model *parent);
    model *get_parent() const;
    uint64_t get_id() const;
};

#endif // SHAPE_HPP
