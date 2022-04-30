#version 330 core
layout (location = 0) in vec3 p;
layout (location = 1) out vec3 nearPoint;
layout (location = 2) out vec3 farPoint;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0f);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, view, projection).xyz;
    farPoint = UnprojectPoint(p.x, p.y, 1.0, view, projection).xyz; 
    gl_Position = vec4(p, 1.0);
}