#pragma once
#include "cgmath.h"

union Vertex {
    struct {
        Vector3 pos;
        Vector2 texcoord;
    };
    float values[5];
};
