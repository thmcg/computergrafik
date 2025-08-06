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

#include "camera.h"
#include "cgmath.h"
#include "scene.h"
#include "settings.h"
#include "window.h"

#include <array>
#include <map>
#include <string>

class Simulation
{
  public:
    Simulation(const Settings &settings, Window &window);
    ~Simulation();
    void loop(const double time, UpdateModelCallback updateModelCallback = {});
    const Vector3 &getCameraPosition();
    const Matrix4 &getCameraViewMatrix();
    size_t loadScene(const std::string &filename, LoadModelCallback loadModelCallback = {});
    void unloadScene(size_t sceneId, UnloadModelCallback unloadModelCallback = {});

  private:
    Camera camera = {};
    double cameraYaw = 0.0;
    double cameraPitch = 0.0;
    double walkSpeed = 0.0;
    double mouseSpeed = 0.0;
    std::array<bool, 384> keyStates = {};
    std::map<size_t, Scene> scenes = {};
    size_t currentSceneId = 0;
};