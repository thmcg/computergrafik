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

#include <string>
#include <map>
#include "cgmath.h"

static bool init = false;
typedef void (*logicFunction)(Vector3&, Vector3&, float&);
static std::map<std::string, logicFunction> functionMap; 

static void earthRotation(Vector3 &position, Vector3 &rotation, float &scale)
{
    rotation.y += 0.0001f;
}

static void logicInit()
{
    functionMap["earthRotation"] = earthRotation;
    init = true;
}

void logicRun(std::string logic, Vector3 &position, Vector3 &rotation, float &scale)
{
    if (!init) logicInit();

    if (functionMap.find(logic) != functionMap.end())
    {
        functionMap[logic](position, rotation, scale);
    }
}
