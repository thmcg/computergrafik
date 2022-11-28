#pragma once
#include <string>
#include <vector>
#include "cgmath.h"

class Entity
{
    public:
    Entity(std::string name);
    ~Entity();
    void setModel(std::string model);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setScale(float scale);
    void addFlag(std::string flag);
    void load();
    void update(double time);

    private:
    int modelId;
    std::string name;
    std::string model;
    Vector3 position;
    Vector3 rotation;
    float scale = 1;
    std::vector<std::string> flags;
};
