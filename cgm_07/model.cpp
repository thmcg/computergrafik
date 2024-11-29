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

#include "model.h"

#include "filereader.h"

Model::Model(const std::string &filename)
{
    FileReader reader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "m")
        {
            // mesh
            std::string meshName = reader.getString();
            mesh.emplace(meshName);
        }
        else if (type == "s")
        {
            // shader
            std::string vertexShaderName = reader.getString();
            std::string fragmentShaderName = reader.getString();
            shader.emplace(vertexShaderName, fragmentShaderName);
        }
        else if (type == "t")
        {
            // texture
            std::string uniformName = reader.getString();
            std::string textureName = reader.getString();
            textures.emplace(uniformName, textureName);
        }
    }
}

Model::~Model()
{
    mesh.reset();
    shader.reset();
    textures.clear();
}

void Model::transform(const Vector3 &position, const Vector3 &rotation, double scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

void Model::render(const Matrix4 &projectionMatrix, const Matrix4 &viewMatrix, const Vector3 &sunDirection)
{
    Matrix4 worldMatrix = Matrix4::translate(position.x, position.y, position.z) * Matrix4::rotate(rotation.x, rotation.y, rotation.z) * Matrix4::scale(scale);

    shader->activate();
    shader->setMatrix4("ProjectionMatrix", projectionMatrix);
    shader->setMatrix4("ViewMatrix", viewMatrix);
    shader->setMatrix4("WorldMatrix", worldMatrix);
    shader->setVector3("SunDirection", sunDirection);
    for (const auto &[uniformName, texture] : textures)
    {
        shader->setTexture(uniformName, texture);
    }

    mesh->draw();
}