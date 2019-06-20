#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "glm/glm.hpp"

#include "shape.hpp"

class sphere: public shape
{
private:
    glm::vec3 center;
    float radius;
    int m, n;
protected:
    void copy(std::shared_ptr<sphere> new_sphere) const;
    virtual void draw() const;
    virtual float intersect(const ray &in) const;
    virtual void apply(glm::mat4 mat);

    virtual buffer _serialize() const;
public:
    sphere(glm::vec3 center, float radius, int m, int n);
    sphere(buffer &buf);
    virtual ~sphere();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;
    bool inside(glm::vec3 point) const;
    glm::vec3 get_center() const;

    virtual uint64_t type_id() const;
    virtual void deserialize(buffer &buf);
};

#endif // SPHERE_HPP
