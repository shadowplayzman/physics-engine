#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;
uniform vec3 trailColor;
void main()
{
FragColor = vec4(trailColor,0.1);
   }