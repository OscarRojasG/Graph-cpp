#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *Window::createWindow()
{
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        printf("Error al crear la ventana");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window; 
}

GLFWwindow *Window::getWindow()
{
    return window;
}

int Window::getHeight()
{
    glfwGetWindowSize(window, &width, &height);
    return height;
}

int Window::getWidth()
{
    glfwGetWindowSize(window, &width, &height);
    return width;
}