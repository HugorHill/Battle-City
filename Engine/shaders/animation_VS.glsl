#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 tex_coord;
out vec2 Tex_coord;
uniform mat4 transform;

void main()
{
	Tex_coord = tex_coord;
	gl_Position = transform*vec4(vertex,1);
}