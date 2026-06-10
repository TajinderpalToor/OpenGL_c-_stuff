//
// Created by tajinderpal on 2026-06-08.
//

#include "../Header Files/VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}
void VAO::LinkAttribute(VBO VBO, GLuint layout,GLuint numComponents,GLenum type,GLuint stride,void* offset){
    VBO.Bind();
    glVertexAttribPointer(layout,numComponents,type,GL_FALSE,stride,offset);
    glEnableVertexAttribArray(layout);

    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID);

}

void VAO::Unbind() {
    glBindVertexArray(0);

}

void VAO::Delete() {

    glDeleteVertexArrays(1, &ID);

}
