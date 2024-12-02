//
// Created by lucas on 01/12/2024.
//

#ifndef GRAVITY_GRAVITYV2_H
#define GRAVITY_GRAVITYV2_H

#include <complex>
#include <vector>
#include <cmath>
#include "vec3.h"
#include "particleV2.h"


void gravity(particleV2& p1, particleV2& p2)
{
    float G = 6.67e-11;
    float ForceMagnitude;
    vec3 diff = p2.position - p1.position;
    float R = diff.Magnitude();
    //get relative positions first
    std::complex<float> point1(0,0);
    std::complex<float> point2(0,0);
    vec3 Force;
    //check if points are in same position (will add behaviour to delete/combine atoms
    // if at same position)
    //std::println("{}",p2.position.x1);
    if(R != 0)
    {
        ForceMagnitude = (G*p1.mass*p2.mass)/(R*R);
        float real = diff.x1/R;
        float imag = diff.x2/R;
        point2.real(real);
        point2.imag(imag);

        Force = vec3(ForceMagnitude*point2.real(), ForceMagnitude*point2.imag(),0);

        p1.force += Force;
        p2.force -= Force;
    }
    else
    {
        //Points lie on eachother
        //define behaviour here
    }

}

std::vector<particleV2> particle_gen()
{
    std::vector<particleV2> particles;
    for(unsigned i = 0; i < 10; i++)
    {
        float a = (float)i/10;
        particleV2 temp = particleV2(vec3(a,a,0));
        if(i == 0)
        {
            temp.mass = 1'000'000.0;
        }
        else
        {
            temp.position.x1 = 0.1*(i+1);
            temp.position.x2 = 0;
            temp.velocity.x2 = -1*sqrt((6.67e-5)/(0.1*(i+1)));
        }

        particles.push_back(temp);
    }
    return particles;
}

std::vector<float> vertexes(const std::vector<particleV2>& particles)
{
    size_t n = particles.size();
    std::vector<float> vertexList{};
    for(unsigned i = 0; i < n; i++)
    {
        float x1 = particles[i].position.x1;
        float x2 = particles[i].position.x2;
        float x3 = particles[i].position.x3;


        float side1 = 0.01;
        //left
        vertexList.push_back((x1 - side1)*9/16);
        vertexList.push_back(x2);
        vertexList.push_back(x3);
        //up
        vertexList.push_back(x1*9/16);
        vertexList.push_back(x2 + side1);
        vertexList.push_back(x3);
        //right
        vertexList.push_back((x1 + side1)*9/16);
        vertexList.push_back(x2);
        vertexList.push_back(x3);
    }
    return vertexList;
}

void solve(std::vector<particleV2>& particles, float time_step = 0.01)
{
    size_t n = size(particles);
    for(signed i = 0; i < n; i++)
    {
        for(unsigned j = i; j < n; j++)
        {
            if(j==i){continue;}
            gravity(particles[i], particles[j]);
        }
    }

    for(unsigned i = 0; i < n; i++)
    {
        particles[i].accel();

        particles[i].timestep(time_step);
        particles[i].force = {0,0,0};
    }
}







//h is the time step
/*
float RungeKuttaMethod(float x, float h, float (*func)(float, float, float), float t=0)
{
    float k1 = func(t,x);
    float k2 = func(t+h/2, x+(h*(k1/2)));
    float k3 = func(t+h/2, x+(h*(k2/2)));
    float k4 = func(t+h, x+(h*k3));
    return x + h*(k1+2*(k2+k3)+k4)/6;
}
*/
#endif //GRAVITY_GRAVITYV2_H
