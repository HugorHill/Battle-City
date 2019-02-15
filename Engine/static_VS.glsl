#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 transf;
out vec2 texture_coord;


void main()
{
	vec3 pos = (transf*vec4(vertexPosition_modelspace,1)).xyz;
	gl_Position.xyz = pos;
	gl_Position.w = 1.0;
	pos = vertexPosition_modelspace;
	texture_coord.xy = (pos.xy+vec2(1,1))*0.5;
	texture_coord.y=1-texture_coord.y;
}