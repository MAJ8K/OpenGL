#pragma once
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* window;
public:
    Window(short,short,const char*);
    ~Window();

    bool update();
};

Window::Window(short width,short height,const char* title)
{
    glfwInit();
    window = glfwCreateWindow(
        width,height,title,NULL,NULL
    );
    glfwMakeContextCurrent(window);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::update(){
    glfwSwapBuffers(window);
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}