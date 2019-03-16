#version 330 core
layout(location = 0) in vec3 vertex_pos;
uniform mat4 transf;
uniform vec2 light_pos;
uniform int count_lights;
out vec2 texture_coord;
out float brightness;

vec2 get_texture_coords()
{
	vec3 pos = vertex_pos;
	vec2 result = (pos.xy+vec2(1,1))*0.5;
	result.y = 1-result.y;
	return result;
}


void main()
{
	vec2 pos = (transf*vec4(vertex_pos,1)).xy;
	if(count_lights>0)
		brightness = min(1, exp(-length(pos-light_pos)) );
	else
		brightness = 1;


	texture_coord = get_texture_coords();
	gl_Position = vec4(pos,0,1);
}