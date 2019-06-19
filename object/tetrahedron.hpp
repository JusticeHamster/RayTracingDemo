#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "shape.hpp"

class tetrahedron: public shape
{
protected:
    void copy(std::shared_ptr<tetrahedron> new_tetrahedron) const;
    virtual void draw() const;
    virtual float intersect(const ray &in) const;
    virtual void apply(glm::mat4 mat);

    virtual buffer _serialize() const;
public:
    tetrahedron();
    tetrahedron(buffer &buf);
    virtual ~tetrahedron();
    virtual glm::vec3 normal(glm::vec3 point) const;
    virtual void hello() const;
    virtual std::shared_ptr<shape> copy() const;

    virtual uint64_t type_id() const;
    virtual void deserialize(buffer &buf);
};

#endif // TETRAHEDRON_HPP
