//
// Created by lucas on 01/12/2024.
//

#ifndef GRAVITY_VEC3_H
#define GRAVITY_VEC3_H

#include <cmath>

class vec3
{
public:
    float x1;
    float x2;
    float x3;

    [[nodiscard]] float Sum() const
    {
        return x1 + x2 + x3;
    }

    [[nodiscard]] float Magnitude() const
    {
        return sqrt(x1*x1 + x2*x2 + x3*x3);
    }

    vec3 operator+(const vec3& a) const
    {
        vec3 out;
        out.x1 = a.x1 + x1;
        out.x2 = a.x2 + x2;
        out.x3 = a.x3 + x3;
        return out;
    }
    vec3 operator-(const vec3& a) const
    {
        vec3 out;
        out.x1 = x1 - a.x1;
        out.x2 = x2 - a.x2;
        out.x3 = x3 - a.x3;
        return out;
    }
    vec3 operator*(const vec3& a) const
    {
        vec3 out;
        out.x1 = x1*a.x1;
        out.x2 = x2*a.x2;
        out.x3 = x3*a.x3;
        return out;
    }

    vec3 operator*(float a) const
    {
        vec3 out;
        out.x1 = x1*a;
        out.x2 = x2*a;
        out.x3 = x3*a;
        return out;
    }
    vec3 operator/(float a) const
    {
        vec3 out;
        out.x1 = x1/a;
        out.x2 = x2/a;
        out.x3 = x3/a;
        return out;
    }

    vec3& operator+=(const vec3& a)
    {
        vec3 out;
        x1 += a.x1;
        x2 += a.x2;
        x3 += a.x3;
        return *this;
    }

    vec3& operator-=(const vec3& a)
    {
        vec3 out;
        x1 -= a.x1;
        x2 -= a.x2;
        x3 -= a.x3;
        return *this;
    }
};

#endif //GRAVITY_VEC3_H
