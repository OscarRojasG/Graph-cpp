#include "Time.h"

float Time::getCurrent()
{
    return glfwGetTime();
}

float Time::getDelta()
{
    current = getCurrent();
    float delta = current - last;
    last = current;
    return delta;
}