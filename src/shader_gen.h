//
// Created by lucas on 30/11/2024.
//

#ifndef GRAVITY_SHADER_GEN_H
#define GRAVITY_SHADER_GEN_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
//#include <print>

//Shader programs
constexpr char vertexShaderSource1[] =R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
//vec4(1.0f, 0.5f, 0.2f, 1.0f);
constexpr char fragmentShaderSource1[] =R"(
#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;

void main()
{
    FragColor = ourColor;
}
)";

static void set_shader_program(std::string vertexShaderSource = vertexShaderSource1,
                        std::string fragmentShaderSource = fragmentShaderSource1) {
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    const char* vertexShaderSourceArray[1];
    vertexShaderSourceArray[0] = vertexShaderSource.c_str();
    const char* fragmentShaderSourceArray[1];
    fragmentShaderSourceArray[0] = fragmentShaderSource.c_str();
    //vertex shader source
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vertexShaderSourceArray, nullptr);
    glCompileShader(vertexShader);
    //fragment shader source
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fragmentShaderSourceArray, nullptr);
    glCompileShader(fragmentShader);
    //SHADER PROGRAM
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);



    //////

    ///funny stuff
    /*
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    */

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


#endif //GRAVITY_SHADER_GEN_H
