/**
 * Computergrafik
 * Copyright (C) 2023 Tobias Reimann
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

#include <iostream>
#include "settings.h"

bool windowCreate(Settings);
bool windowLoop();
void windowDestroy();

bool graphicsStart(Settings);
void graphicsLoop();
void graphicsTerminate();

int main()
{
    std::cout << "Engine starting...\n";

    Settings settings = Settings();

    if (windowCreate(settings) && graphicsStart(settings))
    {
        while (windowLoop())
        {
            graphicsLoop();
        }
        graphicsTerminate();
        windowDestroy();
    }

    std::cout << "Engine terminated.\n";

    return 0;
}