#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shape
{
    public:
        void initializeShape(float *vertices, unsigned int *VAO, unsigned int *VBO);
};

#endif