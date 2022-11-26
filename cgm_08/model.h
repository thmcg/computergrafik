#pragma once
#include <map>
#include <string>
#include "cgmath.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Model
{
    public:
    Model(std::string filename);
    ~Model();
    void setTransform(Vector3, Vector3, float);
    void render(Matrix projectionMatrix, Matrix viewMatrix, Vector3 sunLight, Vector3 cameraPosition);

    private:
    Vector3 position;
    Vector3 rotation;
    float scale = 1;
    Shader* shader;
    Mesh* mesh;
    std::map<std::string, Texture*> textures;
};
