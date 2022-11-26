#version 330 core
layout (location = 0) in vec3 VertPosIn;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    mat4 WvpMatrix = ProjectionMatrix * ViewMatrix * WorldMatrix;
    gl_Position = WvpMatrix * vec4(VertPosIn, 1.0);
}
