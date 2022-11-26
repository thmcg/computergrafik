#pragma once
#include "cgmath.h"

union Vertex {
    struct {
        Vector3 pos;
        Vector2 texcoord;
        Vector3 normal;
    };
    float values[8];
};
