#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 transf;
uniform vec2 light_pos;
out vec2 texture_coord;
out float brightness;



void main()
{
	vec3 pos = (transf*vec4(vertexPosition_modelspace,1)).xyz;
	vec3 lpos = (transf*vec4(light_pos,0,1)).xyz;
	gl_Position.xyz = pos;
	gl_Position.w = 1.0;
	brightness = min(1, exp(-length(pos-lpos)/10.0) );
	pos = vertexPosition_modelspace;
	texture_coord.xy = (pos.xy+vec2(1,1))*0.5;
	texture_coord.y=1-texture_coord.y;
}