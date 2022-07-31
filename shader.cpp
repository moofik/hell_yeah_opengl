//
// Created by moofik on 31.07.22.
//

#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e) {
        CONSOLE_LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n", e.what());
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        CONSOLE_LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        CONSOLE_LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
    }

    this->m_ShaderProgram = glCreateProgram();
    glAttachShader(this->m_ShaderProgram, vertexShader);
    glAttachShader(this->m_ShaderProgram, fragmentShader);
    glLinkProgram(this->m_ShaderProgram);
    glGetProgramiv(this->m_ShaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(this->m_ShaderProgram, 512, nullptr, infoLog);
        CONSOLE_LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(this->m_ShaderProgram);
}

void Shader::setInt(const std::string &name, int value) const {
    int uniformLocation = glGetUniformLocation(this->m_ShaderProgram, name.c_str());
    glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string &name, float value) const {
    int uniformLocation = glGetUniformLocation(this->m_ShaderProgram, name.c_str());
    glUniform1f(uniformLocation, value);
}

void Shader::setBool(const std::string &name, bool value) const {
    int uniformLocation = glGetUniformLocation(this->m_ShaderProgram, name.c_str());
    glUniform1i(uniformLocation, (int) value);
}

void Shader::setMatrix(const std::string &name, float *matrix) {
    GLuint uniformLocation = glGetUniformLocation(this->m_ShaderProgram, name.c_str());
    glUniformMatrix4fv((int) uniformLocation, 1, GL_FALSE, matrix);
}
