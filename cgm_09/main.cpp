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
            .walkSpeed = 1.0,
            .mouseSpeed = 1.0
        };

        Window window("Computergrafik", settings);
        Renderer renderer(settings, window);
        Simulation simulation(settings, window);

        size_t sceneId = simulation.loadScene("scenes/main.scene", [&renderer](const std::string &modelFile, bool fixed) -> size_t
        {
            return renderer.loadModel(modelFile, fixed);
        });

        double deltaTime = 0.0;

        // The main loop consists of 3 ordered components: window -> simulation -> renderer.
        // The window loop handles keyboard/mouse input and records time passed between frames.
        while (window.loop(deltaTime))
        {
            // simulation loop handles gameplay, e.g. moves entities and camera by an internal logic.
            simulation.loop(deltaTime, [&renderer](size_t modelId, Vector3 position, Vector3 rotation, float scale)
            {
                renderer.updateModel(modelId, position, rotation, scale);
            });
            renderer.setViewMatrix(simulation.getCameraViewMatrix());
            renderer.setCameraPosition(simulation.getCameraPosition());
            // The renderer loop draws entities seen through the camera with the given matrices.
            renderer.loop();
        }

        simulation.unloadScene(sceneId, [&renderer](size_t modelId)
        {
            renderer.unloadModel(modelId);
        });
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Engine terminated." << std::endl;
    return EXIT_SUCCESS;
}