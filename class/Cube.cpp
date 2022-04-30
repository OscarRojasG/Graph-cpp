#include "Cube.h"

void Cube::draw(Program program, Window window)
{
    float ratio = window.getWidth() / (float)window.getHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)ratio, 0.01f, 100.0f);
    program.setProjection(projection);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}