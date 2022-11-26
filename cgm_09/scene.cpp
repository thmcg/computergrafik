#include "scene.h"
#include "filereader.h"

Scene::Scene(std::string filename)
{
    FileReader* reader = new FileReader(filename);
    while (reader->hasLine())
    {
        std::string type = reader->getString();
        if (type == "e")
        {
            entities.push_back(new Entity(reader->getString()));
        }
        else if (type == "m")
        {
            entities[entities.size() - 1]->setModel(reader->getString());
        }
        else if (type == "p")
        {
            entities[entities.size() - 1]->setPosition(reader->getVector3());
        }
        else if (type == "r")
        {
            entities[entities.size() - 1]->setRotation(deg2rad(reader->getVector3()));
        }
        else if (type == "f")
        {
            entities[entities.size() - 1]->addFlag(reader->getString());
        }
    }
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->load();
    }
}

Scene::~Scene()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();
}

void Scene::update(double time)
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(time);
    }
}
