#include "filereader.h"

FileReader::FileReader(std::string filename)
{
    fileStream.open(filename);
}

bool FileReader::hasLine()
{
    std::string lineBuffer;
    if (getline(fileStream, lineBuffer))
    {
        lineStream.clear();
        lineStream.str(lineBuffer);
        return true;
    }
    lineStream.clear();
    fileStream.close();
    return false;
}

std::string FileReader::getString()
{
    std::string str;
    lineStream >> str;
    return str;
}

float FileReader::getFloat()
{
    std::string p1;
    lineStream >> p1;
    return stof(p1);
}

Vector2 FileReader::getVector2()
{
    std::string p1, p2;
    lineStream >> p1 >> p2;
    return (Vector2){stof(p1), stof(p2)};
}

Vector3 FileReader::getVector3()
{
    std::string p1, p2, p3;
    lineStream >> p1 >> p2 >> p3;
    return (Vector3){stof(p1), stof(p2), stof(p3)};
}
