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

#include "vertex.h"

Vertex::Vertex(const Vector3 &position, const Vector2 &texCoord)
    : position{static_cast<float>(position.x), static_cast<float>(position.y), static_cast<float>(position.z)},
      texCoord{static_cast<float>(texCoord.x), static_cast<float>(texCoord.y)}
{
}

Vertex::~Vertex()
{
}