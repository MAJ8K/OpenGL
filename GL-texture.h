#pragma once

#include "GL-Render.h"
#define STB_IMAGE_IMPLEMENTATION
#include "res/stb_image.h"

class Texture
{
private:
    uint32_t m_id;
    std::string m_filepath;
    uint8_t* m_localBuffer;
    int m_width, m_height, m_bpp;
public:
    Texture(const std::string&);
    ~Texture();

    void bind(uint8_t);
    void unbind();
};

Texture::Texture(const std::string& path):
    m_filepath(path),m_localBuffer(nullptr),m_width(0),m_height(0),m_bpp(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(path.c_str(),&m_width,&m_height,&m_bpp,4);
    glGenTextures(1,&m_id);
    glBindTexture(GL_TEXTURE_2D,m_id);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_width,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_localBuffer);
    glBindTexture(GL_TEXTURE_2D,0);
    
    if(m_localBuffer)stbi_image_free(m_localBuffer);

    
}

Texture::~Texture()
{
    glDeleteTextures(1,&m_id);
}

void Texture::bind(uint8_t slot = 0){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,m_id);
}
void Texture::unbind(){glBindTexture(GL_TEXTURE_2D,0);}