#version 300 es

precision highp float;

out vec4 FragColor;

in vec2 TexCoord;
uniform float useTexture;
uniform sampler2D textureSampler;
uniform vec4 defaultColor;

void main()
{
    if (useTexture == 1.0)
    {
        FragColor = texture(textureSampler, TexCoord);

        if (FragColor.a < 0.1)
            discard;
    }
    else
    {
        FragColor = defaultColor;
    }
}