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
class intersection;
class loader;

class model: public drawable, public transformable
{
private:
    std::reference_wrapper<loader> ldr;
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
    void draw(glm::vec3 pos, glm::vec3 di) const;
    void rotate();
    void move();
    void scale();
    bool is_light() const;
    intersect_result intersect(ray &in) const;
    intersection BRDF(ray &in, intersect_result ir) const;
};

#endif // MODEL_HPP
