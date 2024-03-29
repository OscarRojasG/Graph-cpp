#version 330 core
layout (location = 0) in vec3 p;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(p, 1.0);
}