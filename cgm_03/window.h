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

#pragma once

#define GLFW_INCLUDE_GLEXT

#include "settings.h"

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
  public:
    Window(const std::string &title, const Settings &settings);
    ~Window();
    bool loop(double &time);
    void printFps();
    void onKeyboardInput(std::function<void(int key, bool state)> callback);
    void onMouseMoved(std::function<void(double deltaX, double deltaY)> callback);
    void onSizeChanged(std::function<void(int width, int height)> callback);

  private:
    GLFWwindow *window = nullptr;
    int width = 0;
    int height = 0;
    bool fullscreen = false;
    double previousTime = 0.0;
    int frameCount = 0;
    double mouseLastX = 0.0;
    double mouseLastY = 0.0;
    std::vector<std::function<void(int key, bool state)>> keyboardInputCallbacks = {};
    std::vector<std::function<void(double deltaX, double deltaY)>> mouseMovedCallbacks = {};
    std::vector<std::function<void(int width, int height)>> sizeChangedCallbacks = {};
};