#version 330 core
uniform sampler2D Texture_pic;

in vec2 Tex_coord;
out vec4 FragColor;

void main()
{
	FragColor = texture(Texture_pic,Tex_coord);
}  