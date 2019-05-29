#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <memory>

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
    const loader &ldr;
    std::vector<std::shared_ptr<shape> > shapes;
    glm::vec3 position;
    glm::vec3 direction;
    bool illuminated;
    glm::vec3 light;
public:
    model(std::vector<std::shared_ptr<shape> > shapes, glm::vec3 position, glm::vec3 direction, bool illuminated, glm::vec3 light);
    virtual ~model();
    void draw(glm::vec3 pos, glm::vec3 di) const;
    void rotate();
    void move();
    void scale();
    float intersect(ray &in) const;
    intersection BRDF(ray &in) const;
};

#endif // MODEL_HPP
