#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    private:
        GLFWwindow *window;
        glm::vec3 pos;
        glm::vec3 front;
        glm::vec3 up;
        float speed;

        float sensitivity;
        float yaw;
        float pitch;
        float lastX;
        float lastY;

    public:
        Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
        {
            this->window = window;
            this->pos = pos;
            this->front = front;
            this->up = up;

            this->yaw = -90.f,
            this->pitch = 0.f,
            this->sensitivity = 0.1;
            this->lastX = 0;
            this->lastY = 0;
        }
        
        glm::mat4 getViewMatrix();
        void setSpeed(float speed);
        void move(GLFWwindow *window);
        void updateAngle(float x, float y);

        bool getFirstMouse();
        float getLastX();
        float getLastY();
        float setLastX(float lastX);
        float setLastY(float lastY);
};

#endif