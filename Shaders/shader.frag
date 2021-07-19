#version 430 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture;

in vec2 v_texCoord;

void main()
{
   color = texture(u_texture,v_texCoord);
   if(color == vec4(0,0,0,1.0)) color = vec4(0.3,0.3,0.3,1.0);
};