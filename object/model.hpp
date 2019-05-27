#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "shape.hpp"
#include "drawable.hpp"
#include "blockable.hpp"
#include "transformable.hpp"

class model: public drawable, public blockable, public transformable
{
private:
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
    intersection intersect(ray &in) const;
};

#endif // MODEL_HPP
