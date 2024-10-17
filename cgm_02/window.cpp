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

#include "window.h"

Window::Window(const std::string &title, Settings settings)
    : width(settings.width), height(settings.height), fullscreen(settings.fullscreen), resized(true), previousTime(0.0), frameCount(0)
{
    glfwSetErrorCallback(onError);
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    if (settings.msaa) glfwWindowHint(GLFW_SAMPLES, 4);
    if (settings.fullscreen)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
    }
    else
    {
        window = glfwCreateWindow(settings.width, settings.height, title.c_str(), nullptr, nullptr);
    }

    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to open window");
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, onKeyboardInput);
    glfwSetFramebufferSizeCallback(window, onFramebufferSizeChanged);
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetWindowUserPointer(window, this);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::onError(int error, const char *description)
{
    std::cout << "Error: " << description << std::endl;
}

void Window::onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Window *instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (instance->fullscreen)
        {
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, nullptr, (mode->width - instance->width) / 2, (mode->height - instance->height) / 2, instance->width, instance->height, GLFW_DONT_CARE);
        }
        else
        {
            glfwGetWindowSize(window, &instance->width, &instance->height);
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        instance->fullscreen = !instance->fullscreen;
    }
}

void Window::onFramebufferSizeChanged(GLFWwindow *window, int width, int height)
{
    Window *instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    instance->width = width;
    instance->height = height;
    instance->resized = true;
}

void Window::printFps()
{
    double currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1.0)
    {
        uint32_t fps = frameCount;
        std::cout << "FPS: " << fps << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }

    frameCount++;
}

bool Window::loop()
{
    if (glfwWindowShouldClose(window)) return false;

    glfwSwapBuffers(window);
    glfwPollEvents();
    printFps();

    return true;
}