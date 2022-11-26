#pragma once
#include <string>
#include "cgmath.h"

class Shader
{
    public:
    Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
    ~Shader();
    void activate();
    void setMatrix(std::string, Matrix);
    void setVector3(std::string, Vector3);

    private:
    unsigned int shaderProgram;
    bool shaderCompile(std::string filename, unsigned int* shader, unsigned int type);
    char* readFile(std::string filename);
};
