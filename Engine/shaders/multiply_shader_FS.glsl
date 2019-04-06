#version 330 core
uniform sampler2D a_pic;
uniform sampler2D b_pic;

in vec2 texture_coord;
out vec4 FragColor;

void main()
{
	FragColor = texture(a_pic,texture_coord).rgba * texture(b_pic,texture_coord).rgba;
}  