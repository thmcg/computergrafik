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

class Camera
{
  public:
    Camera();
    ~Camera();
    void setPosition(Vector3 position);
    const Vector3 &getPosition();
    void setRotation(Vector3 rotation);
    Vector3 getRotation();
    const Matrix4 &getViewMatrix();

  private:
    Vector3 position = Vector3(0.0, 0.0, 0.0);
    Vector3 rotation = Vector3(0.0, 0.0, 0.0); // in rads
    Matrix4 viewMatrix = Matrix4::identity();
    bool changed = false;
};