/**
 * Computergrafik
 * Copyright © 2021-2025 Tobias Reimann
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

#include "entity.h"

Entity::Entity(std::string name)
{
    this->name = name;
}

void Entity::setModelId(uint32_t modelId)
{
    this->modelId = modelId;
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

void Entity::update(double time, const std::map<std::string, ScriptCallback> &scripts, UpdateModelCallback updateModel)
{
    // Perform physics updates here
    if (script != "" && scripts.contains(script))
    {
        scripts.at(script)(position, rotation, time);
    }

    if (updateModel.has_value())
    {
        updateModel.value()(modelId, position, rotation, scale);
    }
}

void Entity::setScript(const std::string &script)
{
    this->script = script;
}

uint32_t Entity::getModelId() const
{
    return modelId;
}

Vector3 Entity::getPosition() const
{
    return position;
}

Vector3 Entity::getRotation() const
{
    return rotation;
}

double Entity::getScale() const
{
    return scale;
}

Entity::~Entity()
{
}