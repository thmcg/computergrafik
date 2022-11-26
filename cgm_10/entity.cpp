#include "entity.h"
#include "logic.h"

int graphicsLoadModel(std::string filename);
void graphicsUpdateModel(int id, Vector3 position, Vector3 rotation, float scale);
void graphicsUpdateModel(int id, std::string flag);
void graphicsUnloadModel(int id);

Entity::Entity(std::string name)
{
    this->name = name;
}

void Entity::setModel(std::string model)
{
    this->model = model;
}
void Entity::setPosition(Vector3 position)
{
    this->position = position;
}
void Entity::setRotation(Vector3 rotation)
{
    this->rotation = rotation;
}
void Entity::setScale(float scale)
{
    this->scale = scale;
}

void Entity::addFlag(std::string flag)
{
    this->flags.push_back(flag);
}

void Entity::addLogic(std::string logic)
{
    this->logic.push_back(logic);
}

void Entity::load()
{
    this->modelId = graphicsLoadModel(this->model);
    for (int i = 0; i < this->flags.size(); i++)
    {
        graphicsUpdateModel(this->modelId, this->flags[i]);
    }
}

void Entity::update(double time)
{
    for (int i = 0; i < logic.size(); i++)
    {
        logicRun(logic[i], position, rotation, scale);
    }

    graphicsUpdateModel(this->modelId, position, rotation, scale);
}

Entity::~Entity()
{
    graphicsUnloadModel(this->modelId);
}