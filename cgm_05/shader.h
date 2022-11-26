#pragma once
#include <string>
#include "cgmath.h"
#include "texture.h"

class Shader
{
    public:
    Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
    ~Shader();
    void activate();
    void setMatrix(std::string, Matrix);
    void setVector3(std::string, Vector3);
    void setTexture(std::string, Texture*);

    private:
    unsigned int shaderProgram;
    std::string textureSlots[16] = { "" };
    bool shaderCompile(std::string filename, unsigned int* shader, unsigned int type);
    char* readFile(std::string filename);
};
