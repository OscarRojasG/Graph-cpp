#include "Plane.h"

unsigned int Plane::createVAO()
{
    glGenVertexArrays(1, &VAO);
}

unsigned int Plane::createVBO()
{
    glGenBuffers(1, &VBO);
}

void Plane::create()
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::draw(Program program, Window window)
{
    glm::mat4 model = glm::mat4(1.0f);
    program.setModel(model);

    float ratio = (float)window.getWidth() / window.getHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)ratio, 0.1f, 100.0f);
    program.setProjection(projection);

    float color[3] = {0.0f, 0.5f, 0.5f};
    program.setColor(color);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}