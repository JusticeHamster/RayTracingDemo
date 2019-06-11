#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include "glm/glm.hpp"

class transformable
{
private:
    bool is_transformable = true;
protected:
    virtual void apply(glm::mat4 mat) = 0;
public:
    void transform(glm::mat4 mat);
    virtual ~transformable();
    void set_transformable(bool is_transformable);
    bool is_transform() const;
};

#endif // TRANSFORMABLE_HPP
