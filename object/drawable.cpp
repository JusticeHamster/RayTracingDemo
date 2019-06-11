#include "drawable.hpp"

#include <QDebug>

drawable::~drawable()
{

}

void drawable::draw_object() const
{
    if (!is_draw()) {
        return;
    }
    draw();
}

bool drawable::is_draw() const
{
    return _draw;
}

void drawable::set_draw(bool _draw)
{
    this->_draw = _draw;
}
