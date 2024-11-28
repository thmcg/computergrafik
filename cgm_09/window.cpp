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

#include <glad/glad.h>
#include <iostream>

Window::Window(const std::string &title, const Settings &settings)
    : width(settings.width), height(settings.height), fullscreen(settings.fullscreen)
{
    glfwSetErrorCallback([](int error, const char *description)
    {
        std::cerr << "GLFW Error: " << description << std::endl;
    });

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    glfwSetWindowUserPointer(window, this);

    glfwGetFramebufferSize(window, &width, &height);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
    {
        Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));

        self->width = width;
        self->height = height;

        for (auto &callback : self->sizeChangedCallbacks)
        {
            callback(width, height);
        }
    });

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if (key == GLFW_KEY_M && action == GLFW_PRESS)
        {
            if (self->fullscreen)
            {
                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(window, nullptr, (mode->width - self->width) / 2, (mode->height - self->height) / 2, self->width, self->height, GLFW_DONT_CARE);
            }
            else
            {
                glfwGetWindowSize(window, &self->width, &self->height);
                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
            self->fullscreen = !self->fullscreen;
        }
        else if (action == GLFW_PRESS || action == GLFW_RELEASE)
        {
            for (auto &callback : self->keyboardInputCallbacks)
            {
                callback(key, action == GLFW_PRESS);
            }
        }
    });

    glfwGetCursorPos(window, &mouseLastX, &mouseLastY);
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPosition, double yPosition)
    {
        Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));

        double deltaX = xPosition - self->mouseLastX;
        double deltaY = yPosition - self->mouseLastY;

        self->mouseLastX = xPosition;
        self->mouseLastY = yPosition;

        for (auto &callback : self->mouseMovedCallbacks)
        {
            callback(deltaX, deltaY);
        }
    });
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::loop(double &time)
{
    if (glfwWindowShouldClose(window)) return false;

    glfwSwapBuffers(window);
    glfwPollEvents();
    printFps();

    double now = glfwGetTime();
    static double lastTime = now;
    time = now - lastTime;
    lastTime = now;

    return true;
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

void Window::onKeyboardInput(std::function<void(int key, bool state)> callback)
{
    keyboardInputCallbacks.push_back(callback);
}

void Window::onMouseMoved(std::function<void(double deltaX, double deltaY)> callback)
{
    mouseMovedCallbacks.push_back(callback);
}

void Window::onSizeChanged(std::function<void(int width, int height)> callback)
{
    callback(width, height);
    sizeChangedCallbacks.push_back(callback);
}