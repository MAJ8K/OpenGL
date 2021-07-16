#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include "GL-buffer.h"

class VertexArray
{
private:
    uint32_t m_id;
public:
    VertexArray(/* args */);
    ~VertexArray();

    void bind();
    void unbind();

    void addBuffer(Buffer*);
    void addLayout();
};

VertexArray::VertexArray(/* args */)
{
    glGenVertexArrays(1,&m_id);
    glBindVertexArray(m_id);
}

VertexArray::~VertexArray(){glDeleteVertexArrays(1,&m_id);}

void VertexArray::bind(){glBindVertexArray(m_id);}
void VertexArray::unbind(){glBindVertexArray(0);}

void VertexArray::addBuffer(Buffer* buffer){
    this->bind();
    buffer->bind();
}

void VertexArray::addLayout(){
    glVertexAttribPointer(
        0, 2,
        GL_FLOAT,GL_FALSE,
        sizeof(float)*2,
        (const void*)0
    );
    glEnableVertexAttribArray(0);
}