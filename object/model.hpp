#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <memory>
#include <tuple>
#include <optional>

#include "glm/glm.hpp"

#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"
#include "helloable.hpp"

class shape;

class model: public drawable, public transformable, public helloable
{
private:
    static uint64_t ID;
    uint64_t id = ++ID;
    std::vector<std::shared_ptr<shape> > shapes;
    glm::vec3 position;
    glm::vec3 direction;
    bool illuminated;
    glm::vec3 light;
protected:
    void draw() const;
    virtual void apply(glm::mat4 mat);
public:
    using intersect_result = std::tuple<std::optional<std::reference_wrapper<shape> >, float>;
    enum distribution {
        diffuse, mirror, phone
    } distribution_type;
    glm::vec3 mirror_param = glm::vec3(1., 0., .5);

    model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position, glm::vec3 direction, bool illuminated, glm::vec3 light, distribution dist = diffuse);
    model(const model &m);
    model(model &&m);
    model &operator=(const model &m);
    model &operator=(model &&m);

    virtual ~model();
    bool is_light() const;
    glm::vec3 get_light() const;
    glm::vec3 get_position() const;
    glm::vec3 get_direction() const;
    intersect_result intersect(const ray &in) const;
    void hello() const;
    uint64_t get_id() const;
};

#endif // MODEL_HPP
