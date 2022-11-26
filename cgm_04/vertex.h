#pragma once
#include "cgmath.h"

union Vertex {
    struct {
        Vector3 pos;
    };
    float values[3];
};
