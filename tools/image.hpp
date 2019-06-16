#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "glm/glm.hpp"

class image
{
private:
    unsigned width, height;
    glm::vec3 *data;
public:
    image(unsigned width, unsigned height);
    ~image();
    unsigned get_width() const;
    unsigned get_height() const;
    void add(glm::vec3 rgb, unsigned x, unsigned y);
    glm::vec3 get(unsigned x, unsigned y);
};

#endif // IMAGE_HPP
