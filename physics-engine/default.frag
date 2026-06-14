#version 330 core
out vec4 Fragcolor;
in vec3 color;
uniform float scale;
void main()
{
Fragcolor = vec4(color, 1.0f);
}
