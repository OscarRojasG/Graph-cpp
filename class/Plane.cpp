#include "Plane.h"

void Plane::draw(Program program, Window window)
{
    float ratio = window.getWidth() / (float)window.getHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.01f, 100.0f);
    program.setProjection(projection);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}