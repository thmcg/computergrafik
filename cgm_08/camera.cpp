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

#include "camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setPosition(Vector3 position)
{
    this->position = position;
    changed = true;
}

const Vector3 &Camera::getPosition()
{
    return this->position;
}

void Camera::setRotation(Vector3 rotation)
{
    this->rotation = rotation;
    changed = true;
}

Vector3 Camera::getRotation()
{
    return this->rotation;
}

const Matrix4 &Camera::getViewMatrix()
{
    if (changed)
    {
        Matrix4 rotation = Matrix4::rotateX(-this->rotation.x) * Matrix4::rotateY(-this->rotation.y) * Matrix4::rotateZ(-this->rotation.z);
        Matrix4 translation = Matrix4::translate(-this->position.x, -this->position.y, -this->position.z);

        viewMatrix = rotation * translation;
        changed = false;
    }

    return viewMatrix;
}