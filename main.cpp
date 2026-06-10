#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <stb/stb_image.h>
#include "Header Files/shaderclass.h"
#include "Header Files/VAO.h"
#include "Header Files/VBO.h"
#include "Header Files/EBO.h"


// array of datatype of glfloat
/*
 GLfloat verticies [] = {
     //Cordinates                                     // Colors
     -0.5f,-0.5f    * float(sqrt(3)) /3,0.0f,       0.8f,0.3f,0.02f,
      0.5f,-0.5f    * float(sqrt(3)) /3,0.0f,       0.8f,0.3f,0.02f,
      0.0f,0.5f     * float(sqrt(3)) * 2 /3,0.0f,   1.8f,0.6f,0.032f,

     -0.5f / 2,0.5f * float(sqrt(3)) /6,0.0f,       0.9f,0.45f,0.17f, //innerleft
      0.5f / 2,0.5f * float(sqrt(3)) /6,0.0f,       0.9f,0.45f,0.17f,//inner right
      0.0f,-0.5f    * float(sqrt(3)) /3,0.0f,       0.8f,0.3f,0.02f, // innner down

};
GLuint indices[] = {
    0,3,5,
    3,2,4,
    5,4,1
};
 };
*/
//changed original triangle to a square with 4 points for the textures part
//does the color have to be this??

/*
 * OPENGL READS IMAGE FROM BOTTOM LEFT CORNER TO TOP RIGHT
 * STB - READS TOP LEFT TO BOTTOM RIGHT
 *
 *
 **/
GLfloat verticies [] = {
    //Cordinates         // Colors          //Texture cordinates (bottom left is 0,0)
    -0.5f,-0.5f,0.0f,    1.0f,0.0f,0.0f,    0.0f,0.0f,
    -0.5f, 0.5f,0.0f,    0.0f,1.0f,0.0f,    0.0f,1.0f,
     0.5f, 0.5f,0.0f,    0.0f,0.0f,1.0f,    1.0f,1.0f,
     0.5f, -0.5f,0.0f,    1.0f,1.0f,1.0f,   1.0f,0.0f,



};
GLuint indices[] = {
    0,2,1,
    0,3,2
};

// verticies for the square

GLfloat squareverticies [] = {

    // positions          // red gradient colors

    //Triangle 1
    0.6f, 0.5f, 0.0f,     0.4f, 0.0f, 0.0f,
    0.8f, 0.5f, 0.0f,     0.8f, 0.0f, 0.0f,
    0.6f, 0.7f, 0.0f,     1.0f, 0.3f, 0.3f,

    //Triangle 2
    0.8f, 0.5f, 0.0f,     0.8f, 0.0f, 0.0f,
    0.8f, 0.7f, 0.0f,     1.0f, 0.1f, 0.1f,
    0.6f, 0.7f, 0.0f,     1.0f, 0.3f, 0.3f
};

int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"YoutubeOpenGL",NULL,NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0,0,800,800);

    Shader shaderProgram("Resources/Shaders/default.vert","Resources/Shaders/orange.frag");
    Shader shaderProgram1("Resources/Shaders/default.vert","Resources/Shaders/red.frag");

    VAO triangle_vao;
    triangle_vao.Bind();
    VBO triangle_vbo(verticies,sizeof(verticies));
    EBO triangle_ebo(indices,sizeof(indices));

    /*
     * Below is
    *   Attribute 0 (position)
        Read 3 floats
        Start at offset 0
     *
     */
    //triangle.vao is now for the square that we put the texture on - fix naming
    triangle_vao.LinkAttribute(triangle_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    triangle_vao.LinkAttribute(triangle_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    triangle_vao.LinkAttribute(triangle_vbo, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));





    triangle_vao.Unbind();
    triangle_vbo.Unbind();
    triangle_ebo.Unbind();

    //---------Textures ------------

    int widthImg,heightImg,numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes =stbi_load("pop_cat.png",&widthImg,&heightImg,&numColCh,0);
    GLuint texture;
    glGenTextures(1,&texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);

    // do you want the image to be GL_NEAREST (keeps pixels as they are -- good for pixel art)
    //GL_LINEAR -> makes image closer to the pixels near by, makes it blurry

    // look into the settings
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // texture repeat glmeat, gl clamp etc, S & T are like the x-y axis
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,widthImg,heightImg,0,GL_RGBA,GL_UNSIGNED_BYTE,bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D,0);
    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID,"tex0");
    shaderProgram.Activate();
    glUniform1i(tex0Uni,0);
    //------------------ SQUARE ------------
    VAO square_vao;
    square_vao.Bind();
    VBO square_vbo(squareverticies,sizeof(squareverticies));

    square_vao.LinkAttribute(square_vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    square_vao.LinkAttribute(square_vbo, 2, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //square_vao.LinkVBO(square_vbo,0);
    square_vao.Unbind();
    square_vbo.Unbind();

    // get the unifiorm id
    GLuint uniID = glGetUniformLocation(shaderProgram.ID,"scale");
    GLuint uniID1 = glGetUniformLocation(shaderProgram1.ID,"scale");
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f,0.13f,0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        glUniform1f(uniID,0.5f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture);
        triangle_vao.Bind();
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        shaderProgram1.Activate();

        square_vao.Bind();
        //glDrawArrays(GL_TRIANGLES,0,6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    triangle_vao.Delete();
    triangle_vbo.Delete();
    triangle_ebo.Delete();
    square_vao.Delete();
    square_vbo.Delete();
    glDeleteTextures(1,&texture);
    shaderProgram.Delete();
    shaderProgram1.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
