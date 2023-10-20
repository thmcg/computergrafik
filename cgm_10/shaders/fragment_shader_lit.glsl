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

in vec2 TexCoord;
in vec3 NormVect;
in vec3 VertPos;
in vec3 SunLightObjSpc;
in vec3 CameraPosObjSpc;

uniform sampler2D Diffuse;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 albedo = vec3(texture(Diffuse, TexCoord));

    float lightIntensity = max(dot(NormVect, -SunLightObjSpc), 0.0);

    vec3 ambient = 0.1 * lightColor * albedo;
    vec3 diffuse = 0.9 * lightIntensity * lightColor * albedo;

    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);
    vec3 reflectDir = reflect(-SunLightObjSpc, NormVect);
    vec3 specular = 0.5 * pow(max(dot(viewDir, reflectDir), 0.0), 16) * lightColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
