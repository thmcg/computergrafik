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

#include <GLFW/glfw3.h>
#include <iostream>
#include "settings.h"

void graphicsSetWindowSize(int, int);

static GLFWwindow *window;
static int windowWidth, windowHeight;
static bool isFullscreen = false;

static void onError(int error, const char *description)
{
    std::cout << "Error: " << description << std::endl;
}

static void onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (isFullscreen)
        {
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, NULL, (mode->width - windowWidth) / 2, (mode->height - windowHeight) / 2, windowWidth, windowHeight, GLFW_DONT_CARE);
        }
        else
        {
            glfwGetWindowSize(window, &windowWidth, &windowHeight);
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        isFullscreen = !isFullscreen;
    }
}

static void onFramebufferSizeChanged(GLFWwindow *window, int width, int height)
{
    graphicsSetWindowSize(width, height);
}

static void printFps()
{
    static double previousTime = 0;
    static int frameCount = 0;
    
    double currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1.0)
    {
        std::cout << "FPS: " << frameCount << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }
    frameCount++;
}

/**
 * Create a new windows.
 */
bool windowCreate(Settings props)
{
    windowWidth = props.width;
    windowHeight = props.height;
    isFullscreen = props.fullscreen;

    glfwSetErrorCallback(onError);
    
    if (!glfwInit())
    {
        std::cout << "Error initilizing graphics.";
        return false;
    }

    if (props.msaa) glfwWindowHint(GLFW_SAMPLES, 4);

    if (props.fullscreen)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, "CGM", monitor, NULL);
    }
    else
    {
        window = glfwCreateWindow(props.width, props.height, "CGM", NULL, NULL);
    }
    if (!window)
    {
        glfwTerminate();
        std::cout << "Error opening window.";
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, onKeyboardInput);
    glfwSetFramebufferSizeCallback(window, onFramebufferSizeChanged);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    graphicsSetWindowSize(w, h);
    return true;
}

/**
 * Called once per frame. Handles Window Events and prepares
 */
bool windowLoop()
{
    if (glfwWindowShouldClose(window)) return false;

    glfwSwapBuffers(window);
    glfwPollEvents();
    printFps();

    return true;
}

void windowDestroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
