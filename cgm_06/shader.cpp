/**
 * Computergrafik
 * Copyright © 2021-2025 Tobias Reimann
 * Copyright © 2024 Lukas Scheurer: Rewritten in modern C++
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "shader.h"

#include <fstream>
#include <glad/glad.h>

Shader::Shader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile)
{
    int success = 0;
    char infoLog[512];

    uint32_t vertexShaderID, fragmentShaderID;

    compile(vertexShaderFile.c_str(), &vertexShaderID, GL_VERTEX_SHADER);
    compile(fragmentShaderFile.c_str(), &fragmentShaderID, GL_FRAGMENT_SHADER);

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to link shader program " + vertexShaderFile + " + " + fragmentShaderFile + ":\n" + infoLog);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgramID);
}

void Shader::activate()
{
    glUseProgram(shaderProgramID);
}

void Shader::setMatrix4(const std::string &uniformName, const Matrix4 &matrix4)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    
    float values[16] = {
        static_cast<float>(matrix4.m11), static_cast<float>(matrix4.m12), static_cast<float>(matrix4.m13), static_cast<float>(matrix4.m14),
        static_cast<float>(matrix4.m21), static_cast<float>(matrix4.m22), static_cast<float>(matrix4.m23), static_cast<float>(matrix4.m24),
        static_cast<float>(matrix4.m31), static_cast<float>(matrix4.m32), static_cast<float>(matrix4.m33), static_cast<float>(matrix4.m34),
        static_cast<float>(matrix4.m41), static_cast<float>(matrix4.m42), static_cast<float>(matrix4.m43), static_cast<float>(matrix4.m44)
    };

    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, values);
}

void Shader::setVector3(const std::string &uniformName, const Vector3 &vector3)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    
    float values[3] = {static_cast<float>(vector3.x), static_cast<float>(vector3.y), static_cast<float>(vector3.z)};

    glUniform3fv(uniformLocation, 1, values);
}

void Shader::setTexture(const std::string &uniformName, Texture *texture)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (uniformLocation >= 0)
    {
        for (int i = 0; i < 16; i++)
        {
            if (textureUnits[i].empty())
            {
                textureUnits[i] = uniformName;
                glUniform1i(uniformLocation, i);
            }
            if (textureUnits[i] == uniformName)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
                break;
            }
        }
    }
}

void Shader::compile(const std::string &filename, uint32_t *shader, uint32_t type)
{
    std::string shaderCode = readFile(filename);
    char *shaderCodeChar = shaderCode.data();

    int success = 0;
    char infoLog[512];

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderCodeChar, nullptr);
    glCompileShader(*shader);
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shader, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile shader " + filename + ":\n" + infoLog);
    }
}

std::string Shader::readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file " + filename);
    }

    std::string content;
    std::string line;
    while (getline(file, line))
    {
        content += (line + "\n");
    }
    file.close();

    return content;
}