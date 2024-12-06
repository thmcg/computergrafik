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
#include "model.h"
#include "settings.h"
#include "window.h"

#include <map>
#include <string>

class Renderer
{
  public:
    Renderer(const Settings &settings, Window &window);
    ~Renderer();
    void loop();
    void setViewMatrix(const Matrix4 &viewMatrix);
    size_t loadModel(const std::string &filename);
    void updateModel(size_t modelId, const Vector3 &position, const Vector3 &rotation, double scale);
    void unloadModel(size_t modelId);

  private:
    void setViewport();
    int viewportWidth = 0;
    int viewportHeight = 0;
    bool resizeViewport = false;
    Matrix4 viewMatrix = Matrix4::translate(0.0, 0.0, -2.0);
    Matrix4 projectionMatrix = Matrix4::identity();
    Vector3 sunDirection = Vector3(1.0, 1.0, 2.0);
    std::map<size_t, Model> models = {};
    size_t currentModelId = 0;
};