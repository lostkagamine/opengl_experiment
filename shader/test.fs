#version 330

in vec3 fs_Position;
in vec2 fs_UV;

void main()
{
    gl_FragColor = vec4(fs_UV.r, 0.f, fs_UV.g, 1.f);
}