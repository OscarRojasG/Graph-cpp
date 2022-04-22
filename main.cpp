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

void processInput(GLFWwindow *window);

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
    
    Program program;
    program.setVertexShader("shader.vert");
    program.setFragmentShader("shader.frag");
    program.createProgram();

    Plane plane;
    plane.create();

    glm::mat4 view;

    Camera camera(
        window.getWindow(),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    Time time;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!glfwWindowShouldClose(window.getWindow()))
    {
        processInput(window.getWindow());

        camera.setSpeed(2.5f * time.getDelta());
        camera.move();
        view = camera.getLookAtMatrix();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();
        program.setView(view);
        plane.draw(program, window);
        
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