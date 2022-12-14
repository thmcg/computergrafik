#include "model.h"
#include "filereader.h"

Model::Model(std::string filename)
{
    FileReader reader = FileReader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "m")
        {
            //mesh
            std::string m = reader.getString();
            this->mesh = new Mesh(m);
        }
        else if (type == "s")
        {
            //shader
            std::string vs = reader.getString();
            std::string fs = reader.getString();
            this->shader = new Shader(vs, fs);
        }
        else if (type == "t")
        {
            //textures
            std::string slot = reader.getString();
            Texture* tex = new Texture(reader.getString().c_str());
            this->textures.insert(std::pair<std::string,Texture*>(slot, tex));
        }
    }
}

void Model::render(Matrix projectionMatrix, Matrix viewMatrix, Vector3 sunLight)
{
    shader->activate();
    shader->setMatrix("ProjectionMatrix", projectionMatrix);
    shader->setMatrix("ViewMatrix", viewMatrix);
    shader->setMatrix("WorldMatrix", matrixTranslate(position.x, position.y, position.z) * matrixRotateXYZ(rotation.x, rotation.y, rotation.z) * matrixScale(scale));
    shader->setVector3("SunLight", sunLight);
    for (const auto& [key, texture] : textures)
    {
        shader->setTexture(key, texture);
    }
    mesh->draw();
}

void Model::setTransform(Vector3 position, Vector3 rotation, float scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Model::~Model()
{
    delete mesh;
    delete shader;
    for (const auto& [key, texture] : textures)
    {
        delete texture;
    }
}
