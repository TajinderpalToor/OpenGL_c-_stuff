// this is not c code, it is the opengl language
// uniform are universal variables, where other shaders and the main can access without vao

#version 330 core
// 0th layout there is a vec 3 that can assign to it

// never declare them if your not going to use them - opengl will delete them
uniform float scale;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec3 bColor;
layout (location =3) in vec2 aTex;
out vec3 color;
out vec3 color2;

out vec2 textCoord;
void main()
{
   gl_Position=vec4(aPos.x+aPos.x*scale,aPos.y+aPos.y*scale,aPos.z+aPos.z*scale,1.0);
   color  = aColor;
   //color2 = bColor;
   textCoord =aTex;
};
