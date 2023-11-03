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

#pragma once
#include <map>
#include <string>
#include "cgmath.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Model
{
    public:
    Model(std::string filename);
    ~Model();
    void setTransform(Vector3, Vector3, float);
    void toggleFlag(std::string flag);
    void render(Matrix projectionMatrix, Matrix viewMatrix, Vector3 sunLight, Vector3 cameraPosition);
    bool skipDepthTesting();

    private:
    bool nodepth = false;
    bool fixed = false;
    Vector3 position;
    Vector3 rotation;
    float scale = 1;
    Shader *shader;
    Mesh *mesh;
    std::map<std::string, Texture*> textures;
};
