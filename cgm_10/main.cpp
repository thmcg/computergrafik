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
#include "renderer.h"
#include "simulation.h"
#include "window.h"

#include <iostream>

int main()
{
    try
    {
        std::cout << "Engine starting..." << std::endl;

        Settings settings = {
            .fullscreen = false,
            .width = 1280,
            .height = 720,
            .msaa = true,
            .vsync = true,
            .culling = true,
            .depth = true,
            .walkSpeed = 2.0,
            .mouseSpeed = 1.0
        };

        Window window("Computergrafik", settings);
        Renderer renderer(settings, window);
        Simulation simulation(settings, window);
        App demoApp(renderer, simulation);

        double deltaTime = 0.0;
        while (window.loop(deltaTime))
        {
            demoApp.update(deltaTime);
            renderer.setViewMatrix(simulation.getCameraViewMatrix());
            renderer.setCameraPosition(simulation.getCameraPosition());
            renderer.loop();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Engine terminated." << std::endl;
    return EXIT_SUCCESS;
}