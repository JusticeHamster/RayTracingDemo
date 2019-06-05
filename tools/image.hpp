#ifndef IMAGE_HPP
#define IMAGE_HPP

class image
{
private:
    unsigned width, height;
public:
    image(unsigned width, unsigned height);
    unsigned get_width() const;
    unsigned get_height() const;
};

#endif // IMAGE_HPP
