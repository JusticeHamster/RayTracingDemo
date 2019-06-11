#include "transformable.hpp"

void transformable::transform(glm::mat4 mat)
{
    if (!is_transform()) {
        return;
    }
    apply(mat);
}

transformable::~transformable()
{

}

void transformable::set_transformable(bool is_transformable)
{
    this->is_transformable = is_transformable;
}

bool transformable::is_transform() const
{
    return is_transformable;
}
