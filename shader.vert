#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 vertexColor;

uniform mat4 model;

void main()
{
    vec4 vec_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = model * vec_Position;
    vertexColor = vec3(1.0f, 0.0f, 0.0f);
}