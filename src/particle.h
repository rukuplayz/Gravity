//
// Created by lucas on 30/11/2024.
//

#ifndef GRAVITY_PARTICLE_H
#define GRAVITY_PARTICLE_H

#include "vec2.h"

class particle
{
public:
    float mass; // kg
    vec2 position;
    vec2 velocity{0,0};
    vec2 force{0,0};

    vec2 acceleration{0,0};

    particle(vec2 pos, float m = 1)
    {
        mass = m;
        position = pos;
    }
    void accel()
    {
        acceleration = force/mass;
    }
    void timestep(float time_step)
    {
        velocity = velocity + acceleration* time_step;
        position = position + (velocity*time_step) + acceleration*time_step*time_step*0.5;
    }
};


#endif //GRAVITY_PARTICLE_H
