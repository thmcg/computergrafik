#pragma once
#include <cmath>

union Vector2 {
    struct {
        float x, y;
    };
    float values[2];
};

union Vector3 {
    struct {
        float x, y, z;
    };
    float values[3];
};

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

inline Matrix operator* (Matrix a, Matrix b)
{
    Matrix m;

    //row 1
    m.m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14;
    m.m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24;
    m.m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34;
    m.m41 = a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44;
    
    //row 2
    m.m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14;
    m.m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24;
    m.m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34;
    m.m42 = a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44;

    //row 3
    m.m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14;
    m.m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24;
    m.m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34;
    m.m43 = a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44;

    //row 4
    m.m14 = a.m14 * b.m11 + a.m24 * b.m12 + a.m34 * b.m13 + a.m44 * b.m14;
    m.m24 = a.m14 * b.m21 + a.m24 * b.m22 + a.m34 * b.m23 + a.m44 * b.m24;
    m.m34 = a.m14 * b.m31 + a.m24 * b.m32 + a.m34 * b.m33 + a.m44 * b.m34;
    m.m44 = a.m14 * b.m41 + a.m24 * b.m42 + a.m34 * b.m43 + a.m44 * b.m44;

    return m;
}

inline Vector3 operator* (Matrix m, Vector3 v)
{
    Vector3 result = {
        m.m11 * v.x + m.m21 * v.y + m.m31 * v.z,
        m.m12 * v.x + m.m22 * v.y + m.m32 * v.z,
        m.m13 * v.x + m.m23 * v.y + m.m33 * v.z
    };
    return result;
}

inline Vector3 operator+ (Vector3 a, Vector3 b)
{
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Matrix matrixTranslate(float x, float y, float z)
{
    Matrix m;
    m.m11 = 1;  m.m21 = 0;  m.m31 = 0;  m.m41 = x;
    m.m12 = 0;  m.m22 = 1;  m.m32 = 0;  m.m42 = y;
    m.m13 = 0;  m.m23 = 0;  m.m33 = 1;  m.m43 = z;
    m.m14 = 0;  m.m24 = 0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

inline Matrix matrixRotateX(float a)
{
    Matrix m;
    m.m11 = 1;  m.m21 =      0;  m.m31 =       0;  m.m41 = 0;
    m.m12 = 0;  m.m22 = cos(a);  m.m32 = -sin(a);  m.m42 = 0;
    m.m13 = 0;  m.m23 = sin(a);  m.m33 =  cos(a);  m.m43 = 0;
    m.m14 = 0;  m.m24 =      0;  m.m34 =       0;  m.m44 = 1;
    return m;
}

inline Matrix matrixRotateY(float a)
{
    Matrix m;
    m.m11 =  cos(a);  m.m21 = 0;  m.m31 = sin(a);  m.m41 = 0;
    m.m12 =       0;  m.m22 = 1;  m.m32 =      0;  m.m42 = 0;
    m.m13 = -sin(a);  m.m23 = 0;  m.m33 = cos(a);  m.m43 = 0;
    m.m14 =       0;  m.m24 = 0;  m.m34 =      0;  m.m44 = 1;
    return m;
}

inline Matrix matrixRotateZ(float a)
{
    Matrix m;
    m.m11 = cos(a);  m.m21 = -sin(a);  m.m31 = 0;  m.m41 = 0;
    m.m12 = sin(a);  m.m22 =  cos(a);  m.m32 = 0;  m.m42 = 0;
    m.m13 =      0;  m.m23 =       0;  m.m33 = 1;  m.m43 = 0;
    m.m14 =      0;  m.m24 =       0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

inline Matrix matrixRotateXYZ(float x, float y, float z)
{
    return matrixRotateX(x) * matrixRotateY(y) * matrixRotateZ(z);
}

inline Matrix matrixScale(float a)
{
    Matrix m;
    m.m11 = a;  m.m21 = 0;  m.m31 = 0;  m.m41 = 0;
    m.m12 = 0;  m.m22 = a;  m.m32 = 0;  m.m42 = 0;
    m.m13 = 0;  m.m23 = 0;  m.m33 = a;  m.m43 = 0;
    m.m14 = 0;  m.m24 = 0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

inline Matrix matrixPerspective(double fov, double aspect, double zNear, double zFar)
{
    //https://wiki.delphigl.com/index.php/glFrustum
    double h = zNear * tan(fov * 0.5);
    double w = h * aspect;

    double left = -w;
    double right = w;
    double bottom = -h;
    double top = h; 

    float m11 = 2 * zNear / (right - left);
    float m22 = 2 * zNear / (top - bottom);
    float m31 = (right + left) / (right - left);
    float m32 = (top + bottom) / (top - bottom);
    float m33 = -(zFar + zNear) / (zFar - zNear);
    float m43 = -2 * zFar * zNear / (zFar - zNear);

    Matrix m;
    m.m11 = m11;  m.m21 =   0;  m.m31 = m31;  m.m41 =   0;
    m.m12 =   0;  m.m22 = m22;  m.m32 = m32;  m.m42 =   0;
    m.m13 =   0;  m.m23 =   0;  m.m33 = m33;  m.m43 = m43;
    m.m14 =   0;  m.m24 =   0;  m.m34 =  -1;  m.m44 =   0;
    return m;
}