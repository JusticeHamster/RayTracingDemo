#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl/opengl_header.hpp"

#include <string>
#include <iostream>

class shader
{
public:
    shader(std::string vertexPath, std::string fragmentPath);
    void use();
    void reload();
    bool loaded() const;
    template<class T> void set(std::string name, T value) const;
private:
    unsigned ID;
    std::string vertexPath;
    std::string fragmentPath;
    bool init = false;
    bool load();
    //
    std::string vertexCode;
    std::string fragmentCode;
};

template<class T>
void shader::set(std::string name, T value) const {
    if constexpr (std::is_floating_point_v<T>) {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    } else {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
    }
}

#endif // SHADER_HPP
