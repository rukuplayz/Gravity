cmake_minimum_required(VERSION 3.29)
project(Gravity)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(glfw-3.4)

add_executable(Gravity src/main.cpp
        src/shader_gen.h
        src/frame1.h
        #src/gravity.h
        #src/particle.h
        #src/vec2.h
        src/particleV2.h
        src/vec3.h
        src/gravityV2.h
)

find_package(OpenGL REQUIRED)

target_link_directories(Gravity PUBLIC lib)
target_link_libraries(Gravity glew32 glfw OpenGL::GL)

target_include_directories(Gravity PUBLIC include)
