#version 330 core
uniform sampler2D pic;
uniform sampler2D light_map;


in vec2 texture_coord;
in vec2 textcoord_light;
out vec4 FragColor;

void main()
{
	FragColor = vec4(texture(pic,texture_coord).rgb*texture(light_map,textcoord_light).r,1);
}  