#version 330 core
layout(location = 0) in vec2 vertex;
out vec2 texture_coord;

vec2 get_texture_coords()
{
	vec2 pos = vertex;
	vec2 result = (pos.xy+vec2(1,1))*0.5;
	return result;
}

void main()
{
	texture_coord = get_texture_coords();
	gl_Position = vec4(vertex,0,1);
}