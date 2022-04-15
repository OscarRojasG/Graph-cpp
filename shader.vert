#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 transform;

void main()
{
    vec4 vec_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = transform * vec_Position;
}