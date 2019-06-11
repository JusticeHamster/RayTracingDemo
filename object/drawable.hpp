#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "glm/glm.hpp"

class drawable
{
protected:
    bool _draw = true;
    virtual void draw() const = 0;
public:
    virtual ~drawable();
    void draw_object() const;
    bool is_draw() const;
    void set_draw(bool _draw);
};

#endif // DRAWABLE_HPP
