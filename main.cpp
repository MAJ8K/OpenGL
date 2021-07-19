#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW-Window.h"
#include "GL-Render.h"
#include "GL-texture.h"
#include "Camera.h"

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
    float x,y,z;//position
    float u,v;//texture
};

Vertex Cube_poss[] = {
    {-0.5f,-0.5f, 0.5f, 0.0f, 0.0f},
    { 0.5f,-0.5f, 0.5f, 1.0f, 0.0f},
    { 0.5f, 0.5f, 0.5f, 1.0f, 1.0f},
    {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f},
    {-0.5f,-0.5f,-0.5f, 0.0f, 0.0f},
    { 0.5f,-0.5f,-0.5f, 1.0f, 0.0f},
    { 0.5f, 0.5f,-0.5f, 1.0f, 1.0f},
    {-0.5f, 0.5f,-0.5f, 0.0f, 1.0f}
};
Vertex Wall_poss[] = {
    {-1.5f,-1.5f,-1.5f, 0.0f, 0.0f},
    { 1.5f,-1.5f,-1.5f, 1.0f, 0.0f},
    { 1.5f, 1.5f,-1.5f, 1.0f, 1.0f},
    {-1.5f, 1.5f,-1.5f, 0.0f, 1.0f}
};

uint32_t indices[] = {
    0,1,2,2,3,0,//front
    6,5,4,4,7,6,//back
    1,0,4,4,5,1,//left
    3,2,6,6,7,3,//right
    0,3,7,7,4,0,//top
    1,5,6,6,2,1,//bottom
};

glm::mat4 GetModel(float a){
    glm::vec3 test = glm::vec3(1.0f);
    glm::vec3* test2 = &test;
    glm::mat4 posMat = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f));
    glm::mat4 rotXMat = glm::rotate(glm::mat4(1.0f),0.0f,glm::vec3(1,0,0));
    glm::mat4 rotYMat = glm::rotate(glm::mat4(1.0f),3.14f * cosf(a),glm::vec3(0,1,0));
    glm::mat4 rotZMat = glm::rotate(glm::mat4(1.0f),3.14f * sinf(a),glm::vec3(0,0,1));
    glm::mat4 sclMat = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f));

    glm::mat4 rotMat = rotZMat * rotYMat * rotXMat;

    return posMat * rotMat * sclMat;

}

int main(int argc, char const *argv[])
{
    Window window(800,600,"Hello World");
    if(glewInit() != GLEW_OK) return -1;

    std::cout << glGetString(GL_VERSION) <<std::endl;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera cam(glm::vec3(0,0,-5.0f),70.0f,4.0f/3.0f,0.01f,1000.0f);

    Buffer vb(GL_ARRAY_BUFFER,Cube_poss,sizeof(Vertex) * 8);
    Buffer ib(GL_ELEMENT_ARRAY_BUFFER,indices,sizeof(uint32_t)*36);
    Buffer vbw(GL_ARRAY_BUFFER,Wall_poss,sizeof(Vertex) * 4);
    Buffer ibw(GL_ELEMENT_ARRAY_BUFFER,indices,sizeof(uint32_t)*6);
    VertexArray vao;
    vao.addBuffer(&vb);
    vao.addBuffer(&ib);
    vao.addLayout();
    VertexArray wva;
    wva.addBuffer(&vbw);
    wva.addBuffer(&ibw);
    wva.addLayout();

    glm::mat4 model = GetModel(0.0f);

    glm::mat4 mvp = cam.getviewproj() * model;

    Program shaders(
        "Shaders/shader.vert",
        "Shaders/shader.frag"
    );
    Program wShad(
        "Shaders/wall.vert",
        "Shaders/wall.frag"
    );
    shaders.bind();

    Renderer renderer;

    Texture texture("Textures/qr-code.png");
    texture.bind(0);

    float r=0,g=0,b=0;
    int location = glGetUniformLocation(shaders.id(),"u_texture");
    glUniform1i(location,0);
    wShad.bind();
    int mvp_loc = glGetUniformLocation(wShad.id(),"u_mvp");
    glUniformMatrix4fv(mvp_loc,1,GL_FALSE,&mvp[0][0]);
        shaders.bind();
    mvp_loc = glGetUniformLocation(shaders.id(),"u_mvp");
    while (window.update())
    {
        cam.setpos(glm::vec3(-5*cosf(g),sinf(b),sinf(g) - 5.0f));
        model = GetModel(r);
        mvp = cam.getviewproj() * model;
        glUniformMatrix4fv(mvp_loc,1,GL_FALSE,&mvp[0][0]);
        glUniform4f(location,cosf(r),tanf(g),sinf(b),1.0f);
        r += 0.01;
        g += 0.025;
        b += 0.001;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.draw(vao,shaders);
        renderer.draw(wva,wShad);
        model = GetModel(0.0f);
        mvp = cam.getviewproj() * model;
        glUniformMatrix4fv(mvp_loc,1,GL_FALSE,&mvp[0][0]);
        shaders.bind();
    }
    return 0;
}
