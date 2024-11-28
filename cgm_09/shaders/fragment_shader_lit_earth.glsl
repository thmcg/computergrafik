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

out vec4 FragColor;

in vec2 TexCoord;
in vec3 NormVec;
in vec3 VertPos;
in vec3 SunDirectionObjSpc;
in vec3 CameraPosObjSpc;

uniform sampler2D Diffuse;
uniform sampler2D Roughness;
uniform sampler2D NormalMap;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 textureColor = vec3(texture(Diffuse, TexCoord));
    float roughness = vec3(texture(Roughness, TexCoord)).r;
    vec3 normal = normalize(texture(NormalMap, TexCoord).rgb * 2.0 - 1.0);

    // ambient
    vec3 ambient = 0.025 * lightColor * textureColor;

    // diffuse
    float lightIntensity = max(dot(normal, SunDirectionObjSpc), 0.0);
    vec3 diffuse = lightIntensity * lightColor * textureColor;

    // specular
    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);
    vec3 reflectDir = reflect(SunDirectionObjSpc, normal);
    vec3 specular = 0.5 * pow(max(dot(viewDir, reflectDir), 0.0), 16) * lightColor * (1.0 - roughness);

    // refraction
    vec3 athmosphereColor = vec3(0.3, 0.4, 0.65);
    float refractionIntensity = (1.0 - max(dot(NormVec, -viewDir), 0.0)) * lightIntensity;

    FragColor = vec4(mix(ambient + diffuse + specular, athmosphereColor, refractionIntensity), 1.0);
}