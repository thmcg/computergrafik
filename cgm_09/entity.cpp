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

#include "entity.h"

int graphicsLoadModel(std::string filename);
void graphicsUpdateModel(int id, Vector3 position, Vector3 rotation, float scale);
void graphicsUpdateModel(int id, std::string flag);
void graphicsUnloadModel(int id);

Entity::Entity(std::string name)
{
    this->name = name;
}

void Entity::setModel(std::string model)
{
    this->model = model;
}

void Entity::setPosition(Vector3 position)
{
    this->position = position;
}

void Entity::setRotation(Vector3 rotation)
{
    this->rotation = rotation;
}

void Entity::setScale(float scale)
{
    this->scale = scale;
}

void Entity::addFlag(std::string flag)
{
    this->flags.push_back(flag);
}

void Entity::load()
{
    this->modelId = graphicsLoadModel(this->model);
    for (int i = 0; i < this->flags.size(); i++)
    {
        graphicsUpdateModel(this->modelId, this->flags[i]);
    }
}

void Entity::update(double time)
{
    graphicsUpdateModel(this->modelId, position, rotation, scale);
}

Entity::~Entity()
{
    graphicsUnloadModel(this->modelId);
}