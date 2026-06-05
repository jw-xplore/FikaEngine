#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
uniform float useTexture = 1;
uniform sampler2D textureSampler;

vec4 defaultColor = vec4(0.8, 0.3, 0.2, 1.0);

void main()
{
    FragColor = mix(defaultColor, texture(textureSampler, TexCoord), useTexture);
}