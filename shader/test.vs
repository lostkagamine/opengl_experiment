#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_UV;
out vec3 fs_Position;
out vec2 fs_UV;

void main()
{
    fs_UV = in_UV;
    fs_Position = in_Position;
    gl_Position = vec4(in_Position, 1.0);
}