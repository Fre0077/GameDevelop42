#version 330 core
in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform float useTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    FragColor = (texColor * useTexture) + (vec4(vertexColor, 1.0) * (1 - useTexture));
}
