#include "shader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile)
{
    int success;
    char infoLog[512];

    unsigned int vertexShader, fragmentShader;
    if (!shaderCompile(vertexShaderFile, &vertexShader, GL_VERTEX_SHADER))
    {
        glDeleteShader(vertexShader);
        return;
    }

    if (!shaderCompile(fragmentShaderFile, &fragmentShader, GL_FRAGMENT_SHADER))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Failed to link shader program" << std::endl << infoLog << std::endl;
        
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(shaderProgram);
}

void Shader::setMatrix(std::string key, Matrix m)
{
    GLint location = glGetUniformLocation(shaderProgram, key.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, m.values);
}

void Shader::setVector3(std::string key, Vector3 v)
{
    GLint location = glGetUniformLocation(shaderProgram, key.c_str());
    glUniform3fv(location, 1, v.values);
}

void Shader::setTexture(std::string key, Texture* texture)
{
    GLint location = glGetUniformLocation(shaderProgram, key.c_str());
    if (location >= 0)
    {
        for (int i = 0; i < 16; i++)
        {
            if (textureSlots[i] == "")
            {
                textureSlots[i] = key;
                glUniform1i(location, i);
            }
            if (textureSlots[i] == key)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, texture->Id);
                break;
            }
        }
    }
}

bool Shader::shaderCompile(std::string filename, unsigned int* shader, unsigned int type)
{
    char * shaderSource = readFile(filename);

    int success;
    char infoLog[512];

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        std::cout << "Failed to compile shader: " << filename << std::endl << infoLog << std::endl;
        return false;
    }
    return true;
}

char* Shader::readFile(std::string filename)
{
    char * shaderSource = 0;
    long length;
    FILE * f = fopen (filename.c_str(), "rb");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        shaderSource = (char*)malloc (length+1);
        if (shaderSource)
        {
            fread (shaderSource, 1, length, f);
            shaderSource[length] = '\0';
        }
        fclose (f);
        return shaderSource;
    }
    return 0;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}