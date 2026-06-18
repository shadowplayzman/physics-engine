#version 330 core
layout (location = 0) in vec3 position;
layout (location= 1) in vec3 acolor;
layout (location=2) in vec2 aTex;

//outputs the vector color,texcoord
out vec3 color;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform float scale;
void main()
{
 gl_Position = camMatrix * vec4(position, 1.0);
color=acolor;
texCoord=aTex;
}