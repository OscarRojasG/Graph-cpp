#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "class/Program.h"
#include "class/Camera.h"
#include "class/Time.h"
#include "class/Window.h"
#include "class/Plane.h"

Camera camera(
    glm::vec3(0.0f,  1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 1.0f),
    glm::vec3(0.0f,  1.0f, 0.0f)
);

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main() {
    glfwInit();

    Window window(800, 600, "Graph");
    window.createWindow();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Error al inicializar Glad");
        return 1;
    } 

    glViewport(0, 0, window.getWidth(), window.getHeight());
    
    Program planeProgram;
    planeProgram.setVertexShader("shader.vert");
    planeProgram.setFragmentShader("shader.frag");
    planeProgram.createProgram();

    Plane plane;
    plane.create();

    glm::mat4 view;

    Time time;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetCursorPosCallback(window.getWindow(), mouse_callback); 
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    while(!glfwWindowShouldClose(window.getWindow()))
    {
        processInput(window.getWindow());

        camera.setSpeed(2.5f * time.getDelta());
        camera.move(window.getWindow());
        view = camera.getViewMatrix();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        planeProgram.use();
        planeProgram.setView(view);
        plane.draw(planeProgram, window);
        
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow *window, double x, double y) {
    if(firstMouse)
    {
        camera.setLastX(x);
        camera.setLastY(y);
        firstMouse = false;
    }
  
    float xoffset = x - camera.getLastX();
    float yoffset = camera.getLastY() - y; 
    camera.setLastX(x);
    camera.setLastY(y);

    camera.updateAngle(xoffset, yoffset);
}