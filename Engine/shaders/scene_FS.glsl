#version 330 core
in vec2 TexCoords;
uniform sampler2D screenTexture;
out vec4 FragColor;

void main()
{
	vec4 vColor = texture(screenTexture, TexCoords.st);
    FragColor = vColor;
}  