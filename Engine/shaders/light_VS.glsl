#version 330 core
layout(location = 0) in vec2 vertex;
out vec2 texture_coord;
out vec2 textcoord_light;
uniform vec2 light_pos;

vec2 get_texture_coords(vec2 v)
{
	vec2 pos = v;
	vec2 result = (pos.xy+vec2(1,1))*0.5;
	return result;
}

void main()
{
	texture_coord = get_texture_coords(vertex);
	textcoord_light = get_texture_coords(vertex-light_pos);
	gl_Position = vec4(vertex,0,1);
}