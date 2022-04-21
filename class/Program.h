#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program
{
    private:
        unsigned int vshader_id;
        unsigned int fshader_id;
        unsigned int program_id;

        void checkShaderErrors(unsigned int shader);
        void checkProgramErrors(unsigned int program);
        const char *readShaderFile(const char *filename);

    public:
        unsigned int createProgram();
        unsigned int setVertexShader(const char *filename);
        unsigned int setFragmentShader(const char *filename);

        void use();
        void setModel(glm::mat4 model);
        void setView(glm::mat4 view);
        void setProjection(glm::mat4 projection);
        void setColor(float rgb[3]);
};

#endif