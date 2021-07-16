#pragma once
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* m_window;
public:
    Window(short,short,const char*);
    ~Window();

    bool update();
};

Window::Window(short width,short height,const char* title)
{
    glfwInit();
    m_window = glfwCreateWindow(
        width,height,title,NULL,NULL
    );
    glfwMakeContextCurrent(m_window);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::update(){
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    return !glfwWindowShouldClose(m_window);
}