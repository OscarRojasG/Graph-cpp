#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

unsigned int createVertexBufferObject();
unsigned int createElementBufferObject();
unsigned int createVertexArrayObject();
unsigned int createVertexShader();
unsigned int createFragmentShader();
unsigned int createShaderProgram();

void checkShaderCompileErrors(unsigned int shader);
void checkShaderProgramErrors(unsigned int program);
const char *readFile(const char *filename);

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
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
    };

    unsigned int VBO = createVertexBufferObject();
    unsigned int EBO = createElementBufferObject();
    unsigned int VAO = createVertexArrayObject();
    unsigned int shaderProgram = createShaderProgram();
    
    
    glm::mat4 model = glm::mat4(1.0f);
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        model = glm::mat4(1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model[0][0]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model[0][0]);
        
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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

unsigned int createShaderProgram()
{ 
    unsigned int vertexShader = createVertexShader();
    unsigned int fragmentShader = createFragmentShader();

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkShaderProgramErrors(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

unsigned int createVertexShader()
{
    const char *vertexShaderSource = readFile("shader.vert");
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader);

    return vertexShader;
}

unsigned int createFragmentShader()
{
    const char *fragmentShaderSource = readFile("shader.frag");
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader);

    return fragmentShader;
}

const char *readFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if(!file)
    {
        printf("Error al abrir el archivo");
        return NULL;
    }

    char *buffer = (char *) malloc(1001 * sizeof(char));
	int size = fread(buffer, sizeof(char), 1000, file);
    buffer[size] = '\0';
    fclose(file);

    return buffer;
}
void checkShaderCompileErrors(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error al compilar el shader: %s", infoLog);
    }
}

void checkShaderProgramErrors(unsigned int program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Error al enlazar los shaders: %s", infoLog);
    }
}