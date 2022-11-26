#include "entity.h"
#include <string>
#include <vector>

class Scene
{
    public:
    Scene(std::string filename);
    ~Scene();
    void update(double time);

    private:
    std::vector<Entity*> entities;
};
