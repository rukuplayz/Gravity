#include <iostream>
//#include <chrono>
#include <thread>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader_gen.h"
#include "frame1.h"

#include "particleV2.h"
#include "gravityV2.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const float vertices2D[] = {-0.5f, -0.5f,
                             0.5f, -0.5f,
                             1.0f,  0.5f};

constexpr char vertexShaderSource2[] =R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const float vertices2[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        1.0f,  0.5f, 0.0f
};

constexpr float vertices3[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        1.0f,  0.5f, 0.0f
};



int main()
{
    //HAS to remain here

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", nullptr, nullptr);
    //800 600
    if (window == nullptr)
    {
        //std::println("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        //std::println(stderr, "Error: {}", (char*)glewGetErrorString(err));
    }
    //std::println(stdout, "Status: Using GLEW {}", (char*)glewGetString(GLEW_VERSION));

    glViewport(0, 0, 1280, 720);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Makes and sets shader program
    set_shader_program();
    int shaderProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    //VAO vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    bool flip = true;

    auto last_time = std::chrono::system_clock::now();
    ////////////////////
    //physics time
    //THE PROBLEM LIES HERE
    std::vector<particleV2> particle_set = particle_gen();
    //Multi threadding should be added at this point to do gravity calculations
    //and run opengl view at the same time

    //const float* input_vertices;

    //need to figure out how to access vertex data and change it
    //without having problems with reading it for the animation/ redraw
    std::vector<float> input_vertices = vertexes(particle_set);
    /*
    std::cout<<"Array is: \n";
    int i;
    for(i=0 ; i<90; i+=3)
        std::println("x: {} y: {} z: {}",input_vertices[i],
                     input_vertices[i+1],
                     input_vertices[i+2]);
        //std::cout<<(float)input_vertices[i]<<"\t";
    */


    float lastTValue = glfwGetTime();
    while(!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        //std::println("{}", timeValue);
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
        //input
        processInput(window);

        //rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        auto now_time(std::chrono::system_clock::now());

        float nowTValue = glfwGetTime();
        float time_step = nowTValue - lastTValue;
        //std::println("{}",time_step);
        solve(particle_set, time_step);
        lastTValue = glfwGetTime();
        input_vertices = vertexes(particle_set);

        //std::println("{}",particle_set[1].acceleration.x1);
        //std::println("{}", particle_set[1].position.x1);

        if((now_time - last_time) > std::chrono::seconds(1))
        {
            flip = !flip;
            last_time = now_time;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        /*
        if(flip)
        {
            frame_gen(VAO, vertices2, std::size(vertices2));
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        else
        {
            frame_gen(VAO, vertices3, std::size(vertices3));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        */

        //frame_gen(VAO, input_vertices, 90);
        frame_genv2(VAO, input_vertices);
        glDrawArrays(GL_TRIANGLES, 0, 90);
        glfwSwapBuffers(window);


        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}