#pragma once
#include "vertex.h"

class Mesh
{
    public:
    Mesh(Vertex*, int);
    ~Mesh();
    void draw();

    private:
    unsigned int VAO, VBO;
    int vertexCount;
    void init(Vertex*, int);
};
