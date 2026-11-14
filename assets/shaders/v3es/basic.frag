#version 300 es

precision highp float;

out vec4 FragColor;

in vec2 TexCoord;
uniform float useTexture;
uniform sampler2D textureSampler;
uniform vec4 defaultColor;

uniform vec2 textureScale;
uniform vec2 textureOffset;

void main()
{
    if (useTexture == 0.0)
    {
        // Plain color
        FragColor = defaultColor;
        return;
    }

    // Texture
    vec2 texturePos = TexCoord * textureScale + textureOffset;
    FragColor = texture(textureSampler, texturePos);

    if (FragColor.a < 0.1)
        discard;
}