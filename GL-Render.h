#pragma once
#include "GL-VertexArray.h"
#include "GL-Shader.h"

class Renderer
{
private:
public:
    Renderer(/* args */);
    ~Renderer();
    
    void draw(VertexArray&,Program&);
};

Renderer::Renderer(/* args */)
{
}

Renderer::~Renderer()
{
}

void Renderer::draw(VertexArray& vao,Program& prog){
    prog.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, vao.vertCount(), GL_UNSIGNED_INT, nullptr);
}