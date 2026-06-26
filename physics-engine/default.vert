#version 330 core
layout (location = 0) in vec3 position;
layout (location=1) in vec3 aNormal;
layout (location= 2) in vec3 acolor;
layout (location=3) in vec2 aTex;

//outputs the vector color,texcoord
out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;


uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model *  vec4(position, 1.0f));
	Normal= mat3(transpose(inverse(model))) *aNormal;
	color=acolor;
	texCoord= aTex;
    gl_Position = camMatrix * vec4(crntPos, 1.0);
}