/**
 * Computergrafik
 * Copyright (C) 2023 Tobias Reimann
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
    bool shaderCompile(std::string filename, unsigned int *shader, unsigned int type);
    char *readFile(std::string filename);
};
