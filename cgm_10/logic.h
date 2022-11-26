#include <string>
#include <map>
#include "cgmath.h"

static bool init = false;
typedef void (*logicFunction)(Vector3&, Vector3&, float&);
static std::map<std::string, logicFunction> functionMap; 

static void earthRotation(Vector3 &position, Vector3 &rotation, float &scale)
{
    rotation.y += 0.0001f;
}

static void logicInit()
{
    functionMap["earthRotation"] = earthRotation;
    init = true;
}

void logicRun(std::string logic, Vector3 &position, Vector3 &rotation, float &scale)
{
    if (!init) logicInit();

    if (functionMap.find(logic) != functionMap.end())
    {
        functionMap[logic](position, rotation, scale);
    }
}
