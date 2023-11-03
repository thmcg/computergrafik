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

#include "model.h"
#include "filereader.h"

Model::Model(std::string filename)
{
    FileReader reader = FileReader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "m")
        {
            //mesh
            std::string m = reader.getString();
            this->mesh = new Mesh(m);
        }
        else if (type == "s")
        {
            //shader
            std::string vs = reader.getString();
            std::string fs = reader.getString();
            this->shader = new Shader(vs, fs);
        }
        else if (type == "t")
        {
            //textures
            std::string slot = reader.getString();
            Texture *tex = new Texture(reader.getString().c_str());
            this->textures.insert(std::pair<std::string,Texture*>(slot, tex));
        }
    }
}

void Model::render(Matrix projectionMatrix, Matrix viewMatrix, Vector3 sunLight, Vector3 cameraPosition)
{
    shader->activate();
    shader->setMatrix("ProjectionMatrix", projectionMatrix);
    shader->setMatrix("ViewMatrix", viewMatrix);
    shader->setMatrix("WorldMatrix", matrixTranslate(position.x, position.y, position.z) * matrixRotateXYZ(rotation.x, rotation.y, rotation.z) * matrixScale(scale));
    shader->setVector3("SunLight", sunLight);
    shader->setVector3("CameraPos", cameraPosition);
    for (const auto& [key, texture] : textures)
    {
        shader->setTexture(key, texture);
    }
    mesh->draw();
}

void Model::setTransform(Vector3 position, Vector3 rotation, float scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Model::~Model()
{
    delete mesh;
    delete shader;
    for (const auto& [key, texture] : textures)
    {
        delete texture;
    }
}
