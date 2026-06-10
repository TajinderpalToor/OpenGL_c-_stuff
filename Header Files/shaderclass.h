//
// Created by tajinderpal on 2026-06-07.
//

#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include<fstream>
#include <cerrno>

std ::string get_file_contents(const char* filename);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertex_path, const char* fragment_path);
    void Activate();
    void Delete();

private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif
