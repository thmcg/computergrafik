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

#include "scene.h"

#include "entity.h"
#include "filereader.h"

#include <iostream>

Scene::Scene(const std::string &filename, LoadModelCallback loadModelCallback)
{
    FileReader reader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "e")
        {
            entities.emplace_back(reader.getString());
        }
        else if (type == "m")
        {
            std::string modelFile = reader.getString();
            std::string flag = reader.getString();
            if (loadModelCallback.has_value())
            {
                entities[entities.size() - 1].setModelId(loadModelCallback.value()(modelFile, flag == "fixed"));
            }
        }
        else if (type == "p")
        {
            entities[entities.size() - 1].setPosition(reader.getVector3());
        }
        else if (type == "r")
        {
            Vector3 rotation = reader.getVector3();
            rotation.x = deg2rad(rotation.x);
            rotation.y = deg2rad(rotation.y);
            rotation.z = deg2rad(rotation.z);
            entities[entities.size() - 1].setRotation(rotation);
        }
        else if (type == "s")
        {
            entities[entities.size() - 1].setScale(reader.getFloat());
        }
        else if (type == "l")
        {
            entities[entities.size() - 1].setScript(reader.getString());
        }
    }
}

Scene::~Scene()
{
    std::cout << "Scene destructor" << std::endl;
    entities.clear();
}

void Scene::update(double time, const std::map<std::string, ScriptCallback> &scripts, UpdateModelCallback updateModel)
{
    for (auto &entity : entities)
    {
        entity.update(time, scripts, updateModel);
    }
}

void Scene::unload(UnloadModelCallback unloadModel)
{
    if (unloadModel.has_value())
    {
        auto unloadModelCallback = unloadModel.value();
        for (auto &entity : entities)
        {
            unloadModelCallback(entity.getModelId());
        }
    }
}