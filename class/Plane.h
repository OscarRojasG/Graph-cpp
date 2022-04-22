#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Window.h"

class Plane
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

        unsigned int VBO;
        unsigned int VAO;
        unsigned int createVBO();
        unsigned int createVAO();

    public:
        Plane()
        {
            createVAO();
            createVBO();
        }

        void create();
        void draw(Program program, Window window);
};