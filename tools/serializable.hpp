#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <vector>

using buffer = std::vector<unsigned char>;

class serializable
{
protected:
    virtual buffer _serialize() const = 0;
public:
    bool need_serialize = true;
    virtual ~serializable();
    buffer serialize() const;
    virtual void deserialize(buffer buf) = 0;
};

#endif // SERIALIZABLE_HPP
