#include "Cube.h"

unsigned int Cube::createVAO()
{
    glGenVertexArrays(1, &VAO);
}

unsigned int Cube::createVBO()
{
    glGenBuffers(1, &VBO);
}

void Cube::create()
{
    createVAO();
    createVBO();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::draw(Program program, Window window)
{
    float ratio = (float)window.getWidth() / window.getHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)ratio, 0.01f, 100.0f);
    program.setProjection(projection);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}