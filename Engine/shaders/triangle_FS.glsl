#version 330 core
uniform float color;
uniform sampler2D scene_pic;
uniform sampler2D brigh_pic;

in vec2 texture_coord;
out vec4 FragColor;

void main()
{
	if(color == -1)
		FragColor = texture(scene_pic,texture_coord).rgba * texture(brigh_pic,texture_coord).rgba;
	else
		FragColor = vec4(vec3(color),1);
}  