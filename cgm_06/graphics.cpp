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
    if (settings.depth) glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f,0.2f,0.2f,1.0f);

    mesh = new Mesh("meshes/thm.obj");
    
    shader = new Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    texture = new Texture("textures/thm_colors.jpg");

    return true;
}

void graphicsLoop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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