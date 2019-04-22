#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl_header.hpp"

#include <string>
#include <iostream>
#include "glm/glm.hpp"

class shader
{
public:
    shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
    void use();
    void reload();
    bool loaded() const;
    constexpr static unsigned LOG_SIZE = 512;
    // set
    void set(const std::string &name, bool  value) const { glUniform1i(getLocation(name), static_cast<int>(value)); }
    void set(const std::string &name, int   value) const { glUniform1i(getLocation(name), value); }
    void set(const std::string &name, float value) const { glUniform1f(getLocation(name), value); }
    void set(const std::string &name, float x, float y) const { glUniform2f(getLocation(name), x, y); }
    void set(const std::string &name, float x, float y, float z) const { glUniform3f(getLocation(name), x, y, z); }
    void set(const std::string &name, float x, float y, float z, float w) const { glUniform4f(getLocation(name), x, y, z, w); }
    void set(const std::string &name, const glm::vec2 &value) const { glUniform2fv(getLocation(name), 1, &value[0]); }
    void set(const std::string &name, const glm::vec3 &value) const { glUniform3fv(getLocation(name), 1, &value[0]); }
    void set(const std::string &name, const glm::vec4 &value) const { glUniform4fv(getLocation(name), 1, &value[0]); }
    void set(const std::string &name, const glm::mat2 &mat)   const { glUniformMatrix2fv(getLocation(name), 1, GL_FALSE, &mat[0][0]); }
    void set(const std::string &name, const glm::mat3 &mat)   const { glUniformMatrix3fv(getLocation(name), 1, GL_FALSE, &mat[0][0]); }
    void set(const std::string &name, const glm::mat4 &mat)   const { glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &mat[0][0]); }
private:
    int getLocation(const std::string &name) const { return glGetUniformLocation(ID, name.c_str()); }
    bool checkErrors(unsigned shader, std::string type);
    //
    unsigned ID;
    std::string vertexPath;
    std::string fragmentPath;
    std::string geometryPath;
    bool init = false;
    bool load();
    //
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
};

#endif // SHADER_HPP
