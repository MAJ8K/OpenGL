#version 430 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture;

void main()
{
   color = vec4(0.5,0.5,0.5,1.0);
};