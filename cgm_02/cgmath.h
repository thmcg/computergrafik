#pragma once
#include <cmath>

union Matrix {
    struct {
        float m11;
        float m12;
        float m13;
        float m14;
        float m21;
        float m22;
        float m23;
        float m24;
        float m31;
        float m32;
        float m33;
        float m34;
        float m41;
        float m42;
        float m43;
        float m44;
    };
    float values[16];
};

inline Matrix matrixTranslate(float x, float y, float z)
{
    Matrix m;
    m.m11 = 1;  m.m21 = 0;  m.m31 = 0;  m.m41 = x;
    m.m12 = 0;  m.m22 = 1;  m.m32 = 0;  m.m42 = y;
    m.m13 = 0;  m.m23 = 0;  m.m33 = 1;  m.m43 = z;
    m.m14 = 0;  m.m24 = 0;  m.m34 = 0;  m.m44 = 1;
    return m;
}
