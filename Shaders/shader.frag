#version 430 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;

in vec2 v_texCoord;
in vec4 v_color;

void main()
{
   color = texture(u_texture,v_texCoord);
   if (color == vec4(0,0,0,1))
      color = vec4(0,0,0,0);
};