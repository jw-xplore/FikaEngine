#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
uniform float useTexture = 1;
uniform sampler2D textureSampler;
uniform vec4 defaultColor = vec4(0.8, 0.3, 0.2, 1.0);

void main()
{
    if (useTexture == 1)
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