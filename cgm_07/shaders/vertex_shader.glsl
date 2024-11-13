/**
 * Computergrafik
 * Copyright © 2021-2024 Tobias Reimann
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

#version 330 core
layout (location = 0) in vec3 VertPos;
layout (location = 1) in vec2 TexCoordIn;

out vec2 TexCoord;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    mat4 WvpMatrix = ProjectionMatrix * ViewMatrix * WorldMatrix;
    TexCoord = TexCoordIn;
    gl_Position = WvpMatrix * vec4(VertPos, 1.0);
}