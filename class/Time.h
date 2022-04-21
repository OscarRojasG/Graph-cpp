#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

class Time
{
    private:
        float current;
        float last;

    public:
        Time()
        {
            current = last = glfwGetTime();
        }

        float getCurrent();
        float getDelta();
};

#endif