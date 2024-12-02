//
// Created by lucas on 02/12/2024.
//

#ifndef GRAVITY_PARTICLEV2_H
#define GRAVITY_PARTICLEV2_H

#include "vec3.h"


class particleV2
{
public:
    float mass = 1; // kg
    vec3 position;
    vec3 velocity{0,0,0};
    vec3 force{0,0,0};

    vec3  acceleration{0,0};

    explicit particleV2(vec3 pos)
    {
        position = pos;
    }
    void accel()
    {
        acceleration = force/mass;
    }
    //Might need chaning for runge kutta method
    void timestep(float time_step)
    {
        velocity = velocity + acceleration* time_step;
        position = position + (velocity*time_step) + acceleration*time_step*time_step*0.5;

    }
};
#endif //GRAVITY_PARTICLEV2_H
