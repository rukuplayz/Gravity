//
// Created by lucas on 30/11/2024.
//

#ifndef GRAVITY_VEC2_H
#define GRAVITY_VEC2_H

class vec2
{
public:
    float x1;
    float x2;

    vec2 operator+(vec2 a) const
    {
        vec2 out;
        out.x1 = a.x1 + x1;
        out.x2 = a.x2 + x2;
        return out;
    }
    vec2 operator-(vec2 a) const
    {
        vec2 out;
        out.x1 = x1 - a.x1;
        out.x2 = x2 - a.x2;
        return out;
    }
    vec2 operator*(double a) const
    {
        vec2 out;
        out.x1 = x1*a;
        out.x2 = x2*a;
        return out;
    }
    vec2 operator/(double a) const
    {
        vec2 out;
        out.x1 = x1/a;
        out.x2 = x2/a;
        return out;
    }

    vec2& operator+=(vec2 a)
    {
        vec2 out;
        x1 += a.x1;
        x2 += a.x2;
        return *this;
    }

    vec2& operator-=(vec2 a)
    {
        vec2 out;
        x1 -= a.x1;
        x2 -= a.x2;
        return *this;
    }
};

#endif //GRAVITY_VEC2_H
