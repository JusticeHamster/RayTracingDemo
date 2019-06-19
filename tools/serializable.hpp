#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "glm/glm.hpp"

#include <vector>
#include <string>

using buffer_value_type = unsigned char;
using buffer = std::vector<buffer_value_type>;

class serializable
{
protected:
    virtual buffer _serialize() const = 0;
public:
    bool need_serialize = true;
    virtual ~serializable();
    buffer serialize() const;
    virtual void deserialize(buffer &buf) = 0;

    static buffer serialize(const buffer_value_type *value, int length);
    static buffer serialize(const glm::vec3 &v);
    static buffer serialize(const glm::mat4 &m);
    static buffer serialize(const std::string &s);
    static void deserialize(buffer &buf, buffer_value_type *value, int length);
    static void deserialize(buffer &buf, glm::vec3 &v);
    static void deserialize(buffer &buf, glm::mat4 &m);
    static void deserialize(buffer &buf, std::string &s);
};

#endif // SERIALIZABLE_HPP
