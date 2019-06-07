#include "image.hpp"

#include <stdexcept>
#include <string>

image::image(unsigned width, unsigned height): width(width), height(height), data(new glm::vec3[width * height])
{

}

image::~image()
{
    delete[] data;
}

unsigned image::get_width() const
{
    return width;
}

unsigned image::get_height() const
{
    return height;
}

void image::set(glm::vec3 rgb, unsigned x, unsigned y)
{
    if (x >= height || y >= width)
        throw new std::out_of_range(
            "x, y should in range: [0, " + std::to_string(height) + "], [0, " + std::to_string(width) + "]"
        );
    data[x * width + y] = rgb;
}

glm::vec3 image::get(unsigned x, unsigned y)
{
    if (x >= height || y >= width)
        throw new std::out_of_range(
            "x, y should in range: [0, " + std::to_string(height) + "], [0, " + std::to_string(width) + "]"
        );
    return data[x * width + y];
}
