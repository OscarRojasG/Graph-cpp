#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Window.h"
#include "Shape.h"

class Cube : private Shape
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

        unsigned int VAO;
        unsigned int VBO;

    public:
        Cube() 
        {
            initializeShape(vertices, &VAO, &VBO);
        }

        void draw(Program program, Window window);
};

#endif