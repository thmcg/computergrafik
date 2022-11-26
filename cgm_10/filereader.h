#include <fstream>
#include <sstream>
#include <string>
#include "cgmath.h"

struct FileReader
{
    FileReader(std::string filename);
    bool hasLine();
    std::string getString();
    float getFloat();
    Vector2 getVector2();
    Vector3 getVector3();

    std::ifstream fileStream;
    std::istringstream lineStream;
};
