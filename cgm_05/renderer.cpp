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

#include "renderer.h"

#include "cgmath.h"

#include <glad.c>
#include <iostream>

Renderer::Renderer(const Settings &settings, Window &window)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSwapInterval(settings.vsync ? 1 : 0);

    if (settings.msaa) glEnable(GL_MULTISAMPLE);
    if (settings.culling) glEnable(GL_CULL_FACE);
    if (settings.depth) glEnable(GL_DEPTH_TEST);

    glClearColor(0.29f, 0.36f, 0.4f, 1.0f);

    window.onSizeChanged([this](int width, int height)
    {
        std::cout << "Resolution: " << width << "x" << height << std::endl;
        viewportWidth = width;
        viewportHeight = height;
        resizeViewport = true;
    });

    std::vector<Vertex> vertices = {
        Vertex({-0.6, 0.0, 0.0}, {0.0, 0.5}),
        Vertex({0.0, -0.6, 0.0}, {0.5, 0.0}),
        Vertex({0.6, 0.0, 0.0}, {1.0, 0.5}),
        Vertex({-0.6, 0.0, 0.0}, {0.0, 0.5}),
        Vertex({0.6, 0.0, 0.0}, {1.0, 0.5}),
        Vertex({0.0, 0.6, 0.0}, {0.5, 1.0})};

    mesh = new Mesh(vertices);
    shader = new Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    texture = new Texture("textures/thm2k.png");
}

Renderer::~Renderer()
{
    delete texture;
    delete shader;
    delete mesh;
}

void Renderer::loop()
{
    setViewport();

    glClear(GL_COLOR_BUFFER_BIT);

    shader->activate();
    shader->setMatrix4("ProjectionMatrix", projectionMatrix);
    shader->setMatrix4("ViewMatrix", viewMatrix);
    shader->setMatrix4("WorldMatrix", Matrix4::identity());
    shader->setTexture("thmTexture", texture);
    mesh->draw();
}

void Renderer::setViewport()
{
    if (resizeViewport)
    {
        resizeViewport = false;
        glViewport(0, 0, viewportWidth, viewportHeight);
        double zNear = 0.1;
        double zFar = 100.0;
        double fov = 0.785; // 45deg

        double aspect = static_cast<double>(viewportWidth) / static_cast<double>(viewportHeight);
        projectionMatrix = Matrix4::perspective(fov, aspect, zNear, zFar);
    }
}

void Renderer::setViewMatrix(const Matrix4 &viewMatrix)
{
    this->viewMatrix = viewMatrix;
}
