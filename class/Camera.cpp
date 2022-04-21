#include "Camera.h"

glm::mat4 Camera::getLookAtMatrix()
{
    return glm::lookAt(pos, pos + front, up);
}

void Camera::setSpeed(float speed)
{
    this->speed = speed;
}

void Camera::move()
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += speed * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= speed * front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(front, up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += glm::normalize(glm::cross(front, up)) * speed;
}