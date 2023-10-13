#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <iostream>
#include "cgmath.h"
#include "settings.h"

static Settings settings;
static int viewportWidth = 0;
static int viewportHeight = 0;
static int resizeViewport = false;
static Matrix viewMatrix = matrixTranslate(0.0f, 0.0f, -2.0f);

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
        Matrix projectionMatrix = matrixPerspective(fov, aspect, zNear, zFar);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(projectionMatrix.values);
    }
}

void graphicsUpdateCamera(Matrix m)
{
    viewMatrix = m;
}

bool graphicsStart(Settings props)
{
    settings = props;
    glfwSwapInterval(props.vsync ? 1 : 0);
    if (settings.msaa) glEnable(GL_MULTISAMPLE);
    if (settings.culling) glEnable(GL_CULL_FACE);
    if (settings.depth) glEnable(GL_DEPTH_TEST);

    glClearColor(0.29f,0.36f,0.4f,1.0f);

    return true;
}

void graphicsLoop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(viewMatrix.values);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.73f, 0.14f);
    glVertex3f(-0.6f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.6f, 0.0f);
    glVertex3f(0.6f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.6f, 0.0f);
    glEnd();
}

void graphicsTerminate()
{

}

void graphicsSetWindowSize(int width, int height)
{
    std::cout << "Resolution: " << width << "x" << height << std::endl;
    viewportWidth = width;
    viewportHeight = height;
    resizeViewport = true;
}