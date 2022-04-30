#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(pos, pos + front, up);
}

void Camera::setSpeed(float speed)
{
    this->speed = speed;
}

void Camera::move(GLFWwindow *window)
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

void Camera::updateAngle(float x, float y)
{
    x *= sensitivity;
    y *= sensitivity;

    yaw += x;
    pitch += y;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}

float Camera::getLastX()
{
    return lastX;
}

float Camera::getLastY()
{
    return lastY;
}

float Camera::setLastX(float lastX)
{
    this->lastX = lastX;
}

float Camera::setLastY(float lastY)
{
    this->lastY = lastY;
}