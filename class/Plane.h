#ifndef PLANE_H
#define PLANE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Window.h"
#include "Shape.h"

class Plane : private Shape
{
    private:
        float vertices[18] = {
            1.0f,  1.0f, 0.0f,
           -1.0f, -1.0f, 0.0f,
           -1.0f,  1.0f, 0.0f,

           -1.0f, -1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };

        unsigned int VAO;
        unsigned int VBO;

    public:
        Plane() 
        {
            initializeShape(vertices, &VAO, &VBO);
        }

        void draw(Program program, Window window);
};

#endif