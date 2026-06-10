//
// Created by tajinderpal on 2026-06-09.
//

// what is glad, stb and all that shit
//set up on work laptop and github
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

# include<glad/glad.h>
#include<stb/stb_image.h>

#include "shaderclass.h"

class Texture {
    public:
    GLuint ID;
    GLenum type;
    Texture (const char* image, GLenum texType, GLenum slot, GLenum format, GLenum 
};
#endif