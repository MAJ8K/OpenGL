#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW-Window.h"

#include <iostream>

struct Size {static const short W = 800, H = 600;};
float positions[6] = {
    0,0.5f,
    0.5f,-0.5f,
    -0.5f,-0.5f
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
            GL_ARRAY_BUFFER,sizeof(float)*6,
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
    while (window.update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3);
    }
    
    return 0;
}
