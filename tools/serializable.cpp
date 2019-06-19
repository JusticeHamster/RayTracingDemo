#include "serializable.hpp"

serializable::~serializable()
{

}

buffer serializable::serialize() const
{
    if (!need_serialize) {
        return {};
    }
    return _serialize();
}

buffer serializable::serialize(const buffer_value_type *value, int length)
{
    buffer b;
    auto p = value;
    for (int i = 0; i < length; ++i) {
        b.push_back(*p++);
    }
    return b;
}

buffer serializable::serialize(const glm::vec3 &v)
{
    buffer b;
    for (int i = 0; i < 3; ++i) {
        buffer t = serialize(reinterpret_cast<const buffer_value_type *>(&v[i]), sizeof(float));
        b.insert(b.end(), t.begin(), t.end());
    }
    return b;
}

buffer serializable::serialize(const glm::mat4 &m)
{
    buffer b;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            buffer t = serialize(reinterpret_cast<const buffer_value_type *>(&m[i][j]), sizeof(float));
            b.insert(b.end(), t.begin(), t.end());
        }
    }
    return b;
}

buffer serializable::serialize(const std::string &s)
{
    buffer b;
    int size = static_cast<int>(s.size());
    for (auto c : s) {
        b.push_back(static_cast<buffer_value_type>(c));
    }
    buffer t = serialize(reinterpret_cast<const buffer_value_type *>(&size), sizeof(int));
    b.insert(b.end(), t.begin(), t.end());
    return b;
}

void serializable::deserialize(buffer &buf, buffer_value_type *value, int length)
{
    auto p = value + length - 1;
    for (int i = 0; i < length; ++i) {
        *p-- = buf.back();
        buf.pop_back();
    }
}

void serializable::deserialize(buffer &buf, glm::vec3 &v)
{
    for (int i = 2; i >= 0; --i) {
        deserialize(buf, reinterpret_cast<buffer_value_type *>(&v[i]), sizeof(float));
    }
}

void serializable::deserialize(buffer &buf, glm::mat4 &m)
{
    for (int i = 3; i >= 0; --i) {
        for (int j = 3; j >= 0; --j) {
            deserialize(buf, reinterpret_cast<buffer_value_type *>(&m[i][j]), sizeof(float));
        }
    }
}

void serializable::deserialize(buffer &buf, std::string &s)
{
    int size;
    deserialize(buf, reinterpret_cast<buffer_value_type *>(&size), sizeof(int));
    s.resize(static_cast<uint64_t>(size));
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        *it = static_cast<char>(buf.back());
        buf.pop_back();
    }
}
