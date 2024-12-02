//
// Created by lucas on 30/11/2024.
//

#ifndef GRAVITY_GRAVITY_H
#define GRAVITY_GRAVITY_H

#include "particle.h"
#include <cmath>
#include <vector>

void gravity(particle& p1, particle& p2)
{
    float PI = 3.141592653589793238462643383279502884197;
    float G = 6.67e-11;
    vec2 diff = p2.position - p1.position;
    float R = sqrt((diff.x1*diff.x1)+(diff.x2*diff.x2));
    if(R == 0)
    {
        R +=0.00000000001;
    }

    float ForceMag = (G*p1.mass*p2.mass)/(R*R);

    //angle from particle 1 to 2

    float angle = atan(diff.x2/diff.x1);//radians

    if((diff.x1 == 0)and (diff.x2 == 0))
    {
        angle = 0;
    }
    else if(p1.position.x2 < p2.position.x2)
    {
        if(p1.position.x1 > p2.position.x1)
            angle = PI + angle;
        else if(p1.position.x1 < p2.position.x1)
        {
            angle = angle;
        }
    }
    else if(p1.position.x2 < p2.position.x2)
    {
        if(p1.position.x1 > p2.position.x1)
        {
            angle = PI + angle;
        }
    }

    int C1 = 1;
    int C2 = 1;
    /*
    if(p1.position.x1 > p2.position.x1)
    {
        C1 = -1;
    }
    if(p1.position.x2 > p2.position.x2)
    {
        C2 = -1;
    }
    */
    vec2 Force = vec2(C1*ForceMag*cos(angle),C2*ForceMag*sin(angle));
    p1.force += Force;
    p2.force -= Force;
}

std::vector<particle> particle_gen()
{
    std::vector<particle> particles;
    //want to spread out particles evenly in a square from 0,0 to 1,1
    //then we can shift all positions by -0.5 in x and y direction to centre it.

    //for now we just generated a line of vectors
    for(int i = 0; i < 10; i++)
    {
        float trans = 0;
        particle temp = particle(vec2((float)i/20 - trans,(float)i/20 - trans));
        if(i == 0)
        {
            temp.mass = 1'000'000.0;
        }
        if(i==1)
        {
            temp.position.x1 = -0.1;
            temp.position.x2 = 0;
            temp.velocity.x1 = i*0.00;
            temp.velocity.x2 = -0.025;
        }

        //std::println("x: {}, y: {}",temp.position.x1, temp.position.x2);
        particles.push_back(temp);
    }

    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 5; j++)
        {
            float trans = 0;
            particle temp2 = particle(vec2((float)i/10,(float)j/10));

            particles.push_back(temp2);
        }

    }


    return particles;
}

float* vertexes(const std::vector<particle>& particles)
{
    size_t n = particles.size();
    static float vertexArray[90];
    //make little triangles;
    for(int i = 0; i<(3*10*3); i+=9)
    {
        float originx=particles[i/9].position.x1;
        float originy=particles[i/9].position.x2;
        float originz=0;
        float side1 = 0.01;
        float side2 = 0.0007;
        //left
        vertexArray[i]= originx - side1;
        vertexArray[i+1]=originy;
        vertexArray[i+2]=originz;
        //up
        vertexArray[i+3]= originx;
        vertexArray[i+4]=originy + side1;
        vertexArray[i+5]=originz;
        //right
        vertexArray[i+6] = originx + side1;
        vertexArray[i+7]=originy;
        vertexArray[i+8]=originz;
        //std::println("{}",vertexArray[i+4]);
    }
    return vertexArray;
}

std::vector<float> vertexesv2(const std::vector<particle>& particles)
{
    size_t n = particles.size();
    std::vector<float> vertexArray(n*3*3, 0);
    //make little triangles;
    for(int i = 0; i<(3*n*3); i+=9)
    {
        float originx=particles[i/9].position.x1;
        float originy=particles[i/9].position.x2;
        float originz=0;
        float side1 = 0.01;
        float side2 = 0.0007;
        //left
        vertexArray[i]= originx - side1;
        vertexArray[i+1]=originy;
        vertexArray[i+2]=originz;
        //up
        vertexArray[i+3]= originx;
        vertexArray[i+4]=originy + side1;
        vertexArray[i+5]=originz;
        //right
        vertexArray[i+6] = originx + side1;
        vertexArray[i+7]=originy;
        vertexArray[i+8]=originz;
        //std::println("{}",vertexArray[i+4]);
    }
    return vertexArray;
}

void solve(std::vector<particle>& particles, float time_step = 0.01)
{
    //float time_step = 0.01;
    size_t length = size(particles);
    for(int i = 0; i < length; i++)
    {
        for(int j = i; j < length; j++)
        {
            if(j==i){continue;}
            gravity(particles[i], particles[j]);

        }
    }
    for(unsigned i=0; i< length; i++)
    {
        particles[i].accel();
        //v = u+at
        //s = ut + 1/2at^2
        particles[i].timestep(time_step);
        particles[i].force = {0,0};
    }
    //
    //std::println("{}", particles[1].acceleration.x1);

}

#endif //GRAVITY_GRAVITY_H
