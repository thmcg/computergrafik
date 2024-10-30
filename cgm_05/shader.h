/**
 * Computergrafik
 * Copyright © 2021-2024 Tobias Reimann
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

#pragma once

#include "cgmath.h"
#include "texture.h"

#include <string>
#include <array>

class Shader
{
  public:
    Shader();
    Shader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);
    ~Shader();
    void activate();
    void setMatrix4(const std::string &uniformName, const Matrix4 &matrix4);
    void setVector3(const std::string &uniformName, const Vector3 &vector3);
    void setTexture(const std::string &textureName, Texture* texture);

  private:
    uint32_t shaderProgramID = 0;
    std::array<std::string, 16> textureUnits = {};
    void compile(const std::string &filename, uint32_t *shader, uint32_t type);
    std::string readFile(const std::string &filename);
};