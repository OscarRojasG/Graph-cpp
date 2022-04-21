#include "Program.h"

unsigned int Program::setVertexShader(const char *filename)
{
    const char *source = readShaderFile(filename);
    unsigned int vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &source, NULL);
    glCompileShader(vshader);

    checkShaderErrors(vshader);
    this->vshader_id = vshader;
    return vshader_id;
}

unsigned int Program::setFragmentShader(const char *filename)
{
    const char *source = readShaderFile(filename);
    unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &source, NULL);
    glCompileShader(fshader);
    
    checkShaderErrors(fshader);
    this->fshader_id = fshader;
    return fshader_id;
}

unsigned int Program::createProgram()
{ 
    unsigned int program = glCreateProgram();
    glAttachShader(program, vshader_id);
    glAttachShader(program, fshader_id);
    glLinkProgram(program);

    checkProgramErrors(program);
    this->program_id = program;
    return program;
}

void Program::checkShaderErrors(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error al compilar shader: %s", infoLog);
    }
}

void Program::checkProgramErrors(unsigned int program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Error al crear programa: %s", infoLog);
    }
}

const char *Program::readShaderFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if(!file)
    {
        printf("Error al abrir el archivo");
        return NULL;
    }

    char *buffer = (char *) malloc(1001 * sizeof(char));
	int size = fread(buffer, sizeof(char), 1000, file);
    buffer[size] = '\0';
    fclose(file);

    return (const char *) buffer;
}

void Program::use()
{
    glUseProgram(program_id);
}

void Program::setModel(glm::mat4 model)
{
    unsigned int loc = glGetUniformLocation(program_id, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}

void Program::setView(glm::mat4 view)
{
    unsigned int loc = glGetUniformLocation(program_id, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
}

void Program::setProjection(glm::mat4 projection)
{
    unsigned int loc = glGetUniformLocation(program_id, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Program::setColor(float rgb[3])
{
    unsigned int loc = glGetUniformLocation(program_id, "color");
    glUniform3fv(loc, 1, rgb);
}

