#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 NormVect;
in vec3 SunLightObjSpc;

uniform sampler2D Diffuse;

void main()
{
    float albedo = texture(Diffuse, TexCoord).r;

    float lightIntensity = max(dot(NormVect, -SunLightObjSpc), 0.0);

    FragColor = vec4(lightIntensity, lightIntensity, lightIntensity, albedo);
}
