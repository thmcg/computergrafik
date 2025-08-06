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

#include <cstdint>
#include <functional>
#include <optional>
#include <string>

using LoadModelCallback = std::optional<std::function<size_t(const std::string &filename, bool fixed)>>;
using UpdateModelCallback = std::optional<std::function<void(size_t modelId, const Vector3 &position, const Vector3 &rotation, float scale)>>;
using UnloadModelCallback = std::optional<std::function<void(size_t modelId)>>;

class Entity
{
  public:
    Entity(std::string name);
    ~Entity();
    void setModelId(uint32_t modelId);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setScale(float scale);
    void load();
    void update(double time, UpdateModelCallback);
    uint32_t getModelId() const;
    Vector3 getPosition() const;
    Vector3 getRotation() const;
    double getScale() const;

  private:
    std::string name;
    uint32_t modelId = 0;
    Vector3 position = Vector3(0, 0, 0);
    Vector3 rotation = Vector3(0, 0, 0);
    double scale = 1.0;
};