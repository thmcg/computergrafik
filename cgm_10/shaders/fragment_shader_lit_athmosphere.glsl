#version 330 core
out vec4 FragColor;

in vec3 NormVect;
in vec3 VertPos;
in vec3 SunLightObjSpc;
in vec3 CameraPosObjSpc;

void main()
{
    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);

    vec3 athmosphereColor = vec3(0.2, 0.3, 0.65);

    float lightIntensity = max(dot(NormVect, -SunLightObjSpc), 0.0);
    float refractionIntensity = 1.0 - max(dot(NormVect, -viewDir), 0.0);

    FragColor = vec4(athmosphereColor * lightIntensity, refractionIntensity);
}
