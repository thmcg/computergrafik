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

#pragma once
#include "cgmath.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include <map>
#include <optional>
#include <string>

class Model
{
  public:
    Model(const std::string &filename, bool fixed);
    ~Model();
    void transform(const Vector3 &position, const Vector3 &rotation, double scale);
    void render(const Matrix4 &projectionMatrix, const Matrix4 &viewMatrix, const Vector3 &sunDirection, const Vector3 &cameraPosition);

  private:
    bool fixed = false;
    Vector3 position = Vector3(0, 0, 0);
    Vector3 rotation = Vector3(0, 0, 0);
    double scale = 1.0;
    std::optional<Shader> shader = {};
    std::optional<Mesh> mesh = {};
    std::map<std::string, Texture> textures = {};
};