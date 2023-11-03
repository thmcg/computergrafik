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

#include <glad.c>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include "cgmath.h"
#include "settings.h"
#include "vertex.h"
#include "model.h"

static Settings settings;
static int viewportWidth = 0;
static int viewportHeight = 0;
static int resizeViewport = false;
static Matrix viewMatrix;
static Matrix projectionMatrix;
static Vector3 cameraPosition;
static Vector3 sunLight = (Vector3){0.577f,-0.577f,-0.577f};
static std::map<int, Model*> models;
static int modelId = 0;

static void setViewport()
{
    if (resizeViewport)
    {
        resizeViewport = false;

        glViewport(0,0, viewportWidth, viewportHeight);
        double zNear = 0.1;
        double zFar = 100.0;
        double fov = 0.785; //45deg
        double aspect = (double)viewportWidth / (double)viewportHeight;
        projectionMatrix = matrixPerspective(fov, aspect, zNear, zFar);
    }
}

void graphicsUpdateCamera(Matrix m, Vector3 cp)
{
    viewMatrix = m;
    cameraPosition = cp;
}

int graphicsLoadModel(std::string filename)
{
    int id = modelId++;
    Model *m = new Model(filename);
    models.insert(std::pair<int,Model*>(id, m));
    return id;
}

void graphicsUpdateModel(int id, Vector3 position, Vector3 rotation, float scale)
{
    models[id]->setTransform(position, rotation, scale);
}

void graphicsUpdateModel(int id, std::string flag)
{
    models[id]->toggleFlag(flag);
}

void graphicsUnloadModel(int id)
{
    delete models[id];
    models.erase(id);
}

bool graphicsStart(Settings props)
{
    settings = props;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    
    glfwSwapInterval(props.vsync ? 1 : 0);
    if (settings.msaa) glEnable(GL_MULTISAMPLE);
    if (settings.culling) glEnable(GL_CULL_FACE);
    if (settings.depth) glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f,0.2f,0.2f,1.0f);

    return true;
}

void graphicsLoop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& [key, model] : models)
    {
        if (settings.depth && model->skipDepthTesting()) glDisable(GL_DEPTH_TEST);
        model->render(projectionMatrix, viewMatrix, sunLight, cameraPosition);
        if (settings.depth && model->skipDepthTesting()) glEnable(GL_DEPTH_TEST);
    }
}

void graphicsTerminate()
{
    for (const auto& [key, model] : models)
    {
        delete model;
    }
    models.clear();
}

void graphicsSetWindowSize(int width, int height)
{
    std::cout << "Resolution: " << width << "x" << height << std::endl;
    viewportWidth = width;
    viewportHeight = height;
    resizeViewport = true;
}