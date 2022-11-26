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
    Model* m = new Model(filename);
    models.insert(std::pair<int,Model*>(id, m));
    return id;
}

void graphicsUpdateModel(int id, Vector3 position, Vector3 rotation, float scale)
{
    models[id]->setTransform(position, rotation, scale);
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

    int thmModel = graphicsLoadModel("models/thm.model");
    graphicsUpdateModel(thmModel, (Vector3){-1,0,0}, (Vector3){}, 1.0);
    int earthModel = graphicsLoadModel("models/earth.model");
    graphicsUpdateModel(earthModel, (Vector3){1,0,0}, (Vector3){}, 1.0);

    return true;
}

void graphicsLoop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& [key, model] : models)
    {
        model->render(projectionMatrix, viewMatrix, sunLight, cameraPosition);
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