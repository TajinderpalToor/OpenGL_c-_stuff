//
// Created by tajinderpal on 2026-06-07.
//
#include "../Header Files/shaderclass.h"

#include <string>

std::string get_file_contents(const char* file_name) {


    //ifstream = input file stream, so the below line reads file in
    //std::ios::binary means read the raw bytes
    std::ifstream in(file_name, std::ios::binary);

    //check that the file was read in okay and if it is
    if (in) {
        // make string to hold the content
        std::string contents;
        // move to end of fie
        in.seekg (0, std::ios::end);
        //the below line, will give you the total bytes of the file
        // does this by checking the last cursor, makes a memory that size, so you can read the data in
        contents.resize (in.tellg());
        // moves cursor back to begining so that you can move stuff into that memory
        in.seekg (0, std::ios::beg);
        // move the stuff into this memory, read it in
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader :: Shader(const char* vertex_path, const char* fragment_path) {
    std :: string vertexcode = get_file_contents(vertex_path);
    std :: string fragmentcode = get_file_contents(fragment_path);

    //store them in character arrays
    const char* vertexSource = vertexcode.c_str();
    const char* fragmentSource = fragmentcode.c_str();


    // create reference to access shader verticies
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexSource,NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader,"VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentSource,NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader,"FRAGMENT");

    // two use the shaders have to wrap them up into shader program
    //GLuint shaderProgram = glCreateProgram();
    ID = glCreateProgram();

    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);
    glLinkProgram(ID);
    compileErrors(ID,"PROGRAM");
    int success;
    char infolog[512];
    glGetProgramiv(ID,GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID,512,NULL,infolog);
        std::cout << "Failed to link shader program" << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader :: compileErrors(unsigned int shader, const char* type) {

    GLint hasCompiled;
    char infolog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader,GL_COMPILE_STATUS,&hasCompiled);
        if (hasCompiled ==GL_FALSE) {
            glGetShaderInfoLog(shader,1024,NULL,infolog);
            std :: cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
        }
    }

    else {
        glGetProgramiv(shader,GL_COMPILE_STATUS,&hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(shader,1024,NULL,infolog);
            std :: cout << "SHADER LINKING ERROR for:" << type << "\n" << std::endl;
        }
    }
}