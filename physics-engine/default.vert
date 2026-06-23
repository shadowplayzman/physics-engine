#version 330 core
layout (location = 0) in vec3 position;
layout (location= 1) in vec3 acolor;
layout (location=2) in vec2 aTex;

//outputs the vector color,texcoord
out vec3 color;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform float scale;
uniform vec2 offset;
void main()
{
gl_Position = vec4(position.x*scale+offset.x, 
				   position.y*scale+offset.y, 
				   position.z, 
				   1.0);
color=acolor;
texCoord=aTex;
}