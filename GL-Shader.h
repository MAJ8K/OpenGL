#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Program
{
private:
    uint32_t m_id;
public:
    Program(const std::string&,const std::string&);
    ~Program();

    void bind();
    void unbind();
    const uint32_t& id(){return m_id;}
};

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


static uint32_t compileShader(const std::string& source, uint32_t type){
    uint32_t id = glCreateShader(type);
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

Program::Program(const std::string& vertFile,const std::string& fragFile)
{
    std::string vertexShader = parseShader(vertFile);
    std::string fragmentShader = parseShader(fragFile);
    m_id = glCreateProgram();
    unsigned int vs = compileShader(vertexShader,GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader,GL_FRAGMENT_SHADER);
    glAttachShader(m_id,vs);
    glAttachShader(m_id,fs);
    glLinkProgram(m_id);
    glValidateProgram(m_id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Program::~Program(){glDeleteProgram(m_id);}

void Program::bind(){glUseProgram(m_id);}
void Program::unbind(){glUseProgram(0);}

