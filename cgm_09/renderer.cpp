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

#include <cstddef>
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

    glClearColor(0.19f, 0.26f, 0.3f, 1.0f);

    window.onSizeChanged([this](int width, int height)
    {
        std::cout << "Resolution: " << width << "x" << height << std::endl;
        viewportWidth = width;
        viewportHeight = height;
        resizeViewport = true;
    });
}

Renderer::~Renderer()
{
    models.clear();
}

void Renderer::loop()
{
    setViewport();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &[key, model] : models)
    {
        model.render(projectionMatrix, viewMatrix, sunDirection, cameraPosition);
    }
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

void Renderer::setCameraPosition(const Vector3 &cameraPosition)
{
    this->cameraPosition = cameraPosition;
}

size_t Renderer::loadModel(const std::string &filename, bool fixed)
{
    size_t modelId = ++currentModelId;
    models.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(modelId),
        std::forward_as_tuple(filename, fixed)
    );
    return modelId;
}

void Renderer::updateModel(size_t modelId, Vector3 position, Vector3 rotation, float scale)
{
    if (auto it = models.find(modelId); it != models.end())
    {
        it->second.transform(position, rotation, scale);
    }
}

void Renderer::unloadModel(size_t modelId)
{
    models.erase(modelId);
}
