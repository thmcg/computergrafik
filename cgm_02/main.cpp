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
#include "window.h"

#include <iostream>
#include <memory>

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
            .depth = false
        };

        Window window("Computergrafik", settings);
        Renderer renderer(settings, window);

        while (window.loop())
        {
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