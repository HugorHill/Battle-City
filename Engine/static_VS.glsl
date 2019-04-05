#version 330 core
layout(location = 0) in vec3 vertex_pos;
uniform mat4 transf;
out vec2 texture_coord;

vec2 get_texture_coords()
{
	vec3 pos = vertex_pos;
	vec2 result = (pos.xy+vec2(1,1))*0.5;
	return result;
}


void main()
{
	vec2 pos = (transf*vec4(vertex_pos,1)).xy;
	texture_coord = get_texture_coords();
	gl_Position = vec4(pos,0,1);
}