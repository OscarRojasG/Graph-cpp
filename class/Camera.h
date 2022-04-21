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

    public:
        Camera(GLFWwindow *window, glm::vec3 pos, glm::vec3 front, glm::vec3 up)
        {
            this->window = window;
            this->pos = pos;
            this->front = front;
            this->up = up;
        }
        
        glm::mat4 getLookAtMatrix();
        void setSpeed(float speed);
        void move();
};

#endif