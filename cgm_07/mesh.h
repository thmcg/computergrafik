#pragma once
#include <string>
#include "vertex.h"

class Mesh
{
    public:
    Mesh(Vertex*, int);
    Mesh(std::string);
    ~Mesh();
    void draw();

    private:
    unsigned int VAO, VBO;
    int vertexCount;
    void init(Vertex*, int);
};
