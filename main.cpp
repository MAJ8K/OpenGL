#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW-Window.h"
#include "GL-Render.h"
#include "GL-texture.h"

#include <iostream>
#include <math.h>

struct Size {static const short W = 800, H = 600;};
float positions[] = {
    -0.5f,-0.5f, 0.0f, 0.0f,
     0.5f,-0.5f, 1.0f, 0.0f,
     0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f
};
struct Vertex
{
    float x,y;//position
    float u,v;//texture
};

uint32_t indices[6] = {
    0,1,2,2,3,0
};

int main(int argc, char const *argv[])
{
    Window window(Size::W,Size::H,"Hello World");
    if(glewInit() != GLEW_OK) return -1;

    std::cout << glGetString(GL_VERSION) <<std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Buffer vb(GL_ARRAY_BUFFER,positions,sizeof(float)* 4 * 4);
    Buffer ib(GL_ELEMENT_ARRAY_BUFFER,indices,sizeof(uint32_t)*6);
    VertexArray vao;
    vao.addBuffer(&vb);
    vao.addBuffer(&ib);
    vao.addLayout();

    Program shaders(
        "Shaders/shader.vert",
        "Shaders/shader.frag"
    );
    shaders.bind();

    Renderer renderer;

    Texture texture("Textures/qr-code.png");
    texture.bind(0);

    float r=0,g=0,b=0;
    int location = glGetUniformLocation(shaders.id(),"u_texture");
    glUniform1i(location,0);
    location = glGetUniformLocation(shaders.id(),"u_color");
    while (window.update())
    {
        glUniform4f(location,cosf(r),tanf(g),sinf(b),1.0f);
        r += 0.01;
        g += 0.01;
        b += 0.01;
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.draw(vao,shaders);
    }
    return 0;
}
