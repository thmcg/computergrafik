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

#include "simulation.h"

Simulation::Simulation(const Settings &settings, Window &window)
{
    walkSpeed = settings.walkSpeed;
    mouseSpeed = settings.mouseSpeed;

    camera.setPosition(Vector3(0.0, 0.0, 2.0));

    window.onKeyboardInput([this](int key, bool state)
    {
        if (key >= 0 && key < keyStates.size())
        {
            keyStates[key] = state > 0;
        }
    });

    window.onMouseMoved([this](double deltaX, double deltaY)
    {
        double yaw = cameraYaw + deltaX * 0.001 * mouseSpeed;
        double pitch = cameraPitch + deltaY * 0.001 * mouseSpeed;

        if (pitch < -M_PI_2) pitch = -M_PI_2;
        if (pitch > M_PI_2) pitch = M_PI_2;

        cameraYaw = yaw;
        cameraPitch = pitch;
    });
}

Simulation::~Simulation()
{
}

void Simulation::loop(const double time)
{
    // A=65; S=83; D=68; W=87
    Vector4 movement(0.0, 0.0, 0.0, 1.0);
    if (keyStates[87]) movement.z -= walkSpeed * time;
    if (keyStates[83]) movement.z += walkSpeed * time;
    if (keyStates[65]) movement.x -= walkSpeed * time;
    if (keyStates[68]) movement.x += walkSpeed * time;

    movement = Matrix4::rotateY(-cameraYaw) * movement;
    camera.setPosition(camera.getPosition() + movement.xyz());
    camera.setRotation(Vector3(-cameraPitch, -cameraYaw, 0.0));
}

/*
    Simulation::getCamera() is returning the wanted camera through this function,
    as the idea of our API for the Simulation component is to provide the currently
    wanted camera for rendering in the format our engine uses. Internally, it
    can manage it's own camera system with one or more cameras and a completely
    different format, if needed.
*/
const Matrix4 &Simulation::getCameraViewMatrix()
{
    return camera.getViewMatrix();
}