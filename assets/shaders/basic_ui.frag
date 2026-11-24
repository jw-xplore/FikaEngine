#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
uniform float useTexture = 0.0;
uniform sampler2D textureSampler;
uniform vec4 defaultColor = vec4(0.8, 0.3, 0.2, 1.0);

uniform vec2 textureScale = vec2(1.0, 1.0);
uniform vec2 textureUVOffset = vec2(0.0, 0.0);

void main()
{
    if (useTexture == 0.0)
    {
        // Plain color
        FragColor = defaultColor;
        return;
    }

    // Texture
    vec2 texturePos = TexCoord * textureScale + textureUVOffset;
    FragColor = texture(textureSampler, texturePos);

    if (FragColor.a < 0.1)
        discard;
}