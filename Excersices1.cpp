//
// Created by tajinderpal on 2026-06-07.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>
#include <ostream>

#include "GLFW/glfw3.h"
// below is for a normal colored triangle

/*
const char* vertexShaderSource = "#version 330 core\n"
"layout (location =0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";
*/

//vertexshader for points

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   gl_PointSize = 30.0;\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f,0.0f,0.2f,1.0f);\n"
"}\n\0";

//square stuff
const char* vertexShaderSource_square =
"#version 330 core\n"
"layout (location = 0) in vec3 bPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(bPos, 1.0);\n"
"   gl_PointSize = 5.0;\n"
"}\n";

const char* fragmentShaderSource_square = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f,0.0f,1.0f,1.0f);\n"
"}\n\0";

/*
 *
int main() {

    // initialzie the window
    glfwInit();

    // what version of opengl -3.3 and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // array of dataset of data points
    // the window is -1 to 1 in both x and y directions
    GLfloat rightangletriangle_verticies [] = {

        -0.5f,0.0f,0.0f,
        -0.5f,0.5f,0.0f,
        0.0f,0.0f,0.0f
    };

    // square

    GLfloat square_verticies [] = {
        -0.5f, 0.0f, 0.0f, // bottom left
         0.0f, 0.0f, 0.0f, // bottom right
         0.0f, 0.5f, 0.0f, // top right
        -0.5f, 0.5f, 0.0f  // top left
    };
    // create the window itseld
    GLFWwindow* window=glfwCreateWindow(500,500,"Excersice 1",NULL,NULL);
    if (window ==NULL) {
        std::cout << "Failed to create GLFW Window" <<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0,0,500,500);
    glEnable(GL_PROGRAM_POINT_SIZE);
    //create references
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
    glLinkProgram(program);

    //for the square
    GLuint vertexShader_square = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader_square, 1, &vertexShaderSource_square, NULL);
    glCompileShader(vertexShader_square);

    GLuint fragmentShader_square = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_square, 1, &fragmentShaderSource_square, NULL);
    glCompileShader(fragmentShader_square);

    GLuint program_square = glCreateProgram();
    glAttachShader(program_square,vertexShader_square);
    glAttachShader(program_square,fragmentShader_square);
    glLinkProgram(program_square);

    // check the program has linked correctly
    int success;
    char infolog[512];
    glGetProgramiv(program_square,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(program_square,512,NULL,infolog);
        std :: cout << "Failed to link the program" <<std::endl;
    }
    glDeleteShader(vertexShader_square);
    glDeleteShader(fragmentShader_square);

    GLuint vao[2];
    GLuint vbo[2];
    glGenBuffers(1,&vbo[0]);
    glGenVertexArrays(1, &vao[0]);
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(rightangletriangle_verticies),rightangletriangle_verticies,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,0,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //for the square

    glGenBuffers(1,&vbo[1]);
    glGenVertexArrays(1, &vao[1]);
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(square_verticies),square_verticies,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,0,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(vao[0]);
        //glDrawArrays(GL_TRIANGLES,0,3);
        glDrawArrays(GL_POINTS,0,3);

        glUseProgram(program_square);
        glBindVertexArray(vao[1]);
        glDrawArrays(GL_LINE_LOOP,0,4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&vao[0]);
    glDeleteBuffers(1,&vbo[0]);
    glDeleteProgram(program);

    glDeleteVertexArrays(1,&vao[1]);
    glDeleteBuffers(1,&vbo[1]);
    glDeleteProgram(program_square);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*
 *
 *continue from 32:27
 **/