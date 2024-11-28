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

#include "app.h"

#include <chrono>

App::App(Renderer &renderer, Simulation &simulation)
    : renderer(renderer), simulation(simulation)
{
    simulation.registerScript("earthRotation", std::bind(&App::earthRotation, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    sceneId = simulation.loadScene("scenes/main.scene", std::bind(&Renderer::loadModel, &renderer, std::placeholders::_1, std::placeholders::_2));
}

App::~App()
{
    simulation.unloadScene(sceneId, std::bind(&Renderer::unloadModel, &renderer, std::placeholders::_1));
}

void App::update(double deltaTime)
{
    simulation.loop(deltaTime, std::bind(&Renderer::updateModel, &renderer, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void App::earthRotation(Vector3 &position, Vector3 &rotation, double deltaTime)
{
    auto time = std::chrono::system_clock::now();
    auto timeSinceEpoch = time.time_since_epoch();
    double secondsSinceEpoch = std::chrono::duration<double>(timeSinceEpoch).count();

    double timeOfDay = std::fmod(secondsSinceEpoch, 86400);
    double earthRotation = timeOfDay / 86400.0 * deg2rad(360) + deg2rad(112.5);

    int timeOfYear = std::fmod(secondsSinceEpoch + 864000.0, 31557600);

    double earthEcliptic = cos(timeOfYear / 31557600.0 * deg2rad(360)) * deg2rad(-23.4) - deg2rad(22.5);

    rotation = Vector3(earthEcliptic, earthRotation, 0);
}