#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

class Buffer
{
private:
    uint32_t m_id;
    int m_type;
    uint8_t m_size;
public:
    Buffer(int,void*,uint8_t);
    ~Buffer();

    void bind();
    void unbind();
};

Buffer::Buffer(int type,void* data,uint8_t size):
    m_type(type),m_size(size)
{
    glGenBuffers(1,&m_id);
    glBindBuffer(type,m_id);
        glBufferData(type,size,data,GL_STATIC_DRAW);
}

Buffer::~Buffer(){glDeleteBuffers(1,&m_id);}

void Buffer::bind(){glBindBuffer(m_type,m_id);}
void Buffer::unbind(){glBindBuffer(m_type,0);}