#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class texture
{
public:
    texture(unsigned int id, std::string type);
    unsigned int id;
    std::string type;
};

#endif // TEXTURE_HPP
