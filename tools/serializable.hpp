#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <vector>

using buffer = std::vector<unsigned char>;

class serializable
{
public:
    virtual ~serializable();
    virtual buffer serialize() const = 0;
    virtual void deserialize(buffer buf) = 0;
};

#endif // SERIALIZABLE_HPP
