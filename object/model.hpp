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

class shape;

class model: public drawable, public transformable
{
private:
    std::vector<std::shared_ptr<shape> > shapes;
    glm::vec3 position;
    glm::vec3 direction;
    bool illuminated;
    glm::vec3 light;
public:
    using intersect_result = std::tuple<std::optional<std::reference_wrapper<const shape> >, float>;
    enum Distribution {
        diffuse, mirror, phone
    };

    model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position, glm::vec3 direction, bool illuminated, glm::vec3 light);
    virtual ~model();
    void draw() const;
    void rotate();
    void move();
    void scale();
    bool is_light() const;
    glm::vec3 get_light() const;
    glm::vec3 get_position() const;
    glm::vec3 get_direction() const;
    intersect_result intersect(const ray &in) const;
};

#endif // MODEL_HPP
