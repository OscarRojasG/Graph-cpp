#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "class/Program.h"
#include "class/Camera.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

unsigned int createVertexBufferObject();
unsigned int createElementBufferObject();
unsigned int createVertexArrayObject();

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graph", NULL, NULL);
    if (window == NULL)
    {
        printf("Error al crear la ventana");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Error al inicializar Glad");
        return 1;
    } 

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f, 
    };
    /*
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    */

    unsigned int VBO = createVertexBufferObject();
    unsigned int EBO = createElementBufferObject();
    unsigned int VAO = createVertexArrayObject();
    
    Program program;
    program.setVertexShader("shader.vert");
    program.setFragmentShader("shader.frag");
    program.createProgram();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float aspectRatio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glm::mat4 view;

    Camera camera(
        window,
        glm::vec3(0.0f, 0.0f, -3.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    float currentFrame, lastFrame, dt;
    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.setSpeed(2.5f * dt);
        camera.move();
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program.getProgram());

        glBindVertexArray(VAO);
        float time = glfwGetTime();

        view = camera.getLookAtMatrix();

        program.setModel(model);
        program.setView(view);
        program.setProjection(projection);

        float r = sin(time/2)  / 2 + 0.5f;
        float g = cos(time/2)  / 2 + 0.5f;
        float b = sin(-time/2) / 2 + 0.5f;
        float color[3] = {r, g, b};
        program.setColor(color);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int createVertexBufferObject()
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    return VBO;
}

unsigned int createElementBufferObject()
{
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    return EBO;
}

unsigned int createVertexArrayObject()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}