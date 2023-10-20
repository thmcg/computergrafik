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
#include "cgmath.h"
#include "settings.h"
#include "shader.h"
#include "mesh.h"
#include "vertex.h"
#include "texture.h"

static Settings settings;
static int viewportWidth = 0;
static int viewportHeight = 0;
static int resizeViewport = false;
static Matrix viewMatrix;
static Matrix projectionMatrix;
static Shader* shader;
static Mesh* mesh;
static Texture* texture;

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

void graphicsUpdateCamera(Matrix m)
{
    viewMatrix = m;
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

    glClearColor(0.29f,0.36f,0.4f,1.0f);

    Vertex vertices[] = {
        { -0.6f,  0.0f, 0.0f,    0.0f, 0.5f },
        {  0.0f, -0.6f, 0.0f,    0.5f, 0.0f },
        {  0.6f,  0.0f, 0.0f,    1.0f, 0.5f },
        { -0.6f,  0.0f, 0.0f,    0.0f, 0.5f },
        {  0.6f,  0.0f, 0.0f,    1.0f, 0.5f },
        {  0.0f,  0.6f, 0.0f,    0.5f, 1.0f },
    };
    mesh = new Mesh(vertices, 6);
    
    shader = new Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    texture = new Texture("textures/thm2k.png");

    return true;
}

void graphicsLoop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT);

    shader->activate();
    shader->setMatrix("ProjectionMatrix", projectionMatrix);
    shader->setMatrix("ViewMatrix", viewMatrix);
    shader->setMatrix("WorldMatrix", matrixTranslate(0,0,0));
    shader->setTexture("Diffuse", texture);
    mesh->draw();
}

void graphicsTerminate()
{
    delete shader;
    delete mesh;
    delete texture;
}

void graphicsSetWindowSize(int width, int height)
{
    std::cout << "Resolution: " << width << "x" << height << std::endl;
    viewportWidth = width;
    viewportHeight = height;
    resizeViewport = true;
}