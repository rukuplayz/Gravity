//
// Created by lucas on 30/11/2024.
//

#ifndef GRAVITY_FRAME1_H
#define GRAVITY_FRAME1_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

constexpr float vertices1[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

static void frame_gen(unsigned int& VAO, const float* vertices = vertices1,
                      size_t arrayLength = std::size(vertices1))
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, arrayLength*sizeof(float), vertices, GL_DYNAMIC_DRAW);


    ////////////////////////

    glBindVertexArray(VAO);

    //vertex data interpreter
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


}

static void frame_genv2(unsigned int& VAO, const std::vector<float>& vertices)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size(vertices)*sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);


    ////////////////////////

    glBindVertexArray(VAO);

    //vertex data interpreter
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

static void frame_color_gen(unsigned int& VAO, const std::vector<float>& particles)
{

}

#endif //GRAVITY_FRAME1_H
