#version 330 core

out vec4 FragColor;
in vec3 color2;

void main()
{
    FragColor = vec4(color2, 1.0);
}