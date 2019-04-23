#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class texture
{
public:
    texture(unsigned int id, std::string type, std::string path);
    unsigned int id;
    std::string type;
    std::string path;
};

#endif // TEXTURE_HPP
