#include "settings.h"
#include "cgmath.h"
#include <iostream>

void graphicsUpdateCamera(Matrix);

static bool gameKeyState[256] = {};
static Vector3 cameraPosition = {0.0, 0.0, 2.0};
static double cameraYaw = 0;
static double cameraPitch = 0;
double walkSpeed = 1.0;
double mouseSpeed = 1.0;

void gameSetKey(int key, int state)
{
    gameKeyState[key] = state > 0;
}

void gameSetMouse(double dx, double dy)
{
    double yaw = cameraYaw + dx * 0.001 * mouseSpeed;
    double pitch = cameraPitch + dy * 0.001 * mouseSpeed;
    
    if (pitch < -M_PI_2) pitch = -M_PI_2;
    if (pitch > M_PI_2) pitch = M_PI_2;

    cameraYaw = yaw;
    cameraPitch = pitch;
}

void gameLoad(Settings settings)
{
    mouseSpeed = settings.mouseSpeed;
    walkSpeed = settings.walkSpeed;
}

void gameLoop(double time)
{
    //A=65; S=83; D=68; W=87
    Vector3 movement = {};
    if (gameKeyState[87]) movement.z -= walkSpeed * time;
    if (gameKeyState[83]) movement.z += walkSpeed * time;
    if (gameKeyState[65]) movement.x -= walkSpeed * time;
    if (gameKeyState[68]) movement.x += walkSpeed * time;

    movement = matrixRotateY(-cameraYaw) * movement;
    cameraPosition = cameraPosition + movement;

    Matrix tMatrix = matrixTranslate(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z);
    Matrix yMatrix = matrixRotateY(cameraYaw);
    Matrix xMatrix = matrixRotateX(cameraPitch);

    graphicsUpdateCamera(xMatrix * yMatrix * tMatrix);
}

void gameUnload() {}