#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 uv;

uniform vec2 screenSize;
uniform vec2 size;
uniform vec2 position;

out vec2 TexCoord;

void main()
{
    vec2 offset = (vec2(0.0, -size.y) / screenSize) + vec2(-1.0, 1.0);
    vec2 invertedPosition = vec2(position.x, -position.y);
    vec2 target = (aPos / screenSize) * size + (invertedPosition / screenSize) + offset;
    gl_Position = vec4(target, 0.0, 1.0);
    TexCoord = uv;
}