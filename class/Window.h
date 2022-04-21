#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
    private:
        GLFWwindow *window;
        int width;
        int height;
        const char *title;

    public:
        Window(int width, int height, const char *title)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            this->width = width;
            this->height = height;
            this->title = title;
        }

        GLFWwindow *createWindow();
        GLFWwindow *getWindow();
        int getWidth();
        int getHeight();
};

#endif