#version 330 core
out vec4 Fragcolor;

//imports the color vector from vert files
in vec3 color;

//imports the texcoord 
in vec2 texCoord;

uniform sampler2D tex0;
void main()
{
Fragcolor = texture(tex0,texCoord);
}
