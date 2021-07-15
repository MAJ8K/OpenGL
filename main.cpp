#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW-Window.h"
#include "GL-Shader.h"

#include <iostream>

struct Size {static const short W = 800, H = 600;};
float positions[] = {
    -0.5f,-0.5f,
     0.5f,-0.5f,
     0.5f, 0.5f,
    -0.5f, 0.5f,
};
unsigned int indicies[6] = {
    0,1,2,2,3,0
};

int main(int argc, char const *argv[])
{
    Window window(Size::W,Size::H,"Hello World");
    if(glewInit() != GLEW_OK) return -1;

    std::cout << glGetString(GL_VERSION) <<std::endl;

    uint32_t buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);{
        glBufferData(
            GL_ARRAY_BUFFER,sizeof(float)*4,
            positions,GL_STATIC_DRAW
        );
        //layout
        glVertexAttribPointer(
            0, 2,
            GL_FLOAT,GL_FALSE,
            sizeof(float)*2,
            (const void*)0
        );
        glEnableVertexAttribArray(0);
    }
    uint32_t ibo;
    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);{
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indicies, GL_STATIC_DRAW);
    }
    std::string vertexShader = parseShader("Shaders/shader.vert");
    std::string fragmentShader = parseShader("Shaders/shader.frag");
    unsigned int shader = createShader(vertexShader,fragmentShader);
    glUseProgram(shader);

    while (window.update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
    glDeleteProgram(shader);
    return 0;
}
