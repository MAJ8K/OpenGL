#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static unsigned int compileShader(const std::string& source, unsigned int type){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "shader failed" << message << std::endl;
    }

    return id;
}
static unsigned int createShader(
    const std::string& vertexShader,
    const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader,GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader,GL_FRAGMENT_SHADER);
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

static std::string parseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss;
    while (getline(stream, line))
    {
        ss << line << '\n';
    }
    return ss.str();
}