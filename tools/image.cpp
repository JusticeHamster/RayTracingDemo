#include "image.hpp"

image::image(unsigned width, unsigned height): width(width), height(height)
{

}

unsigned image::get_width() const
{
    return width;
}

unsigned image::get_height() const
{
    return height;
}
