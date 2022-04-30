#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Window.h"

class Cube
{
    private:
        float vertices[36*3] = {
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

        unsigned int VBO;
        unsigned int VAO;
        void create();
        unsigned int createVBO();
        unsigned int createVAO();

    public:
        Cube() 
        {
            create();
        }

        void draw(Program program, Window window);
};