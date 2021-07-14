#vertex shader
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_texCoord = texCoord;
}

#fragment shader
#version 330 core

in vec2 v_texCoord;

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
    vec4 texColor = texture(u_texture, v_texCoord);
    color = texColor;
}