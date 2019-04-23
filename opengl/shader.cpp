#include "shader.hpp"

#include <fstream>
#include <sstream>

using namespace std;

shader::shader(string vertexPath, string fragmentPath, string geometryPath):
    vertexPath(vertexPath), fragmentPath(fragmentPath), geometryPath(geometryPath) {
    ;
}

bool shader::loaded() const {
    return init;
}

void shader::reload() {
    init = false;
}

bool shader::checkErrors(unsigned shader, string type) {
    int success;
    char log[LOG_SIZE];
    if (type == "program") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, LOG_SIZE, nullptr, log);
            cout << log << endl;
            return false;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, LOG_SIZE, nullptr, log);
            cout << log << endl;
            return false;
        }
    }
    return true;
}

bool shader::load() {
    ifstream vShaderFile;
    ifstream fShaderFile;
    ifstream gShaderFile;
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode =  fShaderStream.str();
        if (geometryPath != "") {
            gShaderFile.open(geometryPath);
            stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    } catch (ifstream::failure f) {
        cout << f.what() << endl;
        return false;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    unsigned vertex, fragment, geometry;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    if (!checkErrors(vertex, "vertex")) {
        return false;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    if (!checkErrors(fragment, "fragment")) {
        return false;
    }

    if (geometryPath != "") {
        geometry = glCreateShader(GL_GEOMETRY_SHADER_EXT);
        glShaderSource(geometry, 1, &gShaderCode, nullptr);
        glCompileShader(geometry);
        if (!checkErrors(geometry, "geometry")) {
            return false;
        }
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    if (!checkErrors(ID, "program")) {
        return false;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void shader::use() {
    if (!init) {
        if (!load()) {
            return;
        }
        init = true;
    }
    glUseProgram(ID);
}
