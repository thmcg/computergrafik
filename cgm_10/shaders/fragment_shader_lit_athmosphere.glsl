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

#version 330 core
out vec4 FragColor;

in vec3 NormVect;
in vec3 VertPos;
in vec3 SunLightObjSpc;
in vec3 CameraPosObjSpc;

void main()
{
    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);

    vec3 athmosphereColor = vec3(0.2, 0.3, 0.65);

    float lightIntensity = max(dot(NormVect, -SunLightObjSpc), 0.0);
    float refractionIntensity = 1.0 - max(dot(NormVect, -viewDir), 0.0);

    FragColor = vec4(athmosphereColor * lightIntensity, refractionIntensity);
}
