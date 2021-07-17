#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;
out vec4 v_color;

void main()
{
   if(gl_VertexID == 0){
      v_texCoord = vec2(0.0,0.0);
      v_color = vec4(1.0,0.0,0.0,1.0);
   }
   if(gl_VertexID == 1){
      v_texCoord = vec2(1.0,0.0);
      v_color = vec4(0.0,1.0,0.0,1.0);
   }
   if(gl_VertexID == 2){
      v_texCoord = vec2(1.0,1.0);
      v_color = vec4(0.0,0.0,1.0,1.0);
   }
   if(gl_VertexID == 3){
      v_texCoord = vec2(0.0,1.0);
      v_color = vec4(0,0,0,1);
   }
   gl_Position = position;
};