#vertex shader
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
}

#fragment shader
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
   color = u_color;
}