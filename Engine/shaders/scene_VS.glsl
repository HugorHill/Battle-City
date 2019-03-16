#version 330 core
layout(location = 0) in vec3 vertex;
out vec2 TexCoords;

vec2 get_texture_coords(vec3 v)
{
	vec3 pos = v;
	vec2 result = (pos.xy+vec2(1,1))*0.5;
	return result;
}

void main()
{
	gl_Position = vec4(vertex,1);
	TexCoords = get_texture_coords(vertex);
}