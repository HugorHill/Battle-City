#version 330 core
in vec2 TexCoords;
in vec2 bgTexCoords;
out vec4 color;

uniform sampler2D text;
uniform sampler2D bgTexture;
uniform vec3 textColor;
uniform float useBgTexture;


void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
	vec3 resul_color = mix(textColor,texture(bgTexture,bgTexCoords).rgb,useBgTexture);
    color = vec4(resul_color, 1.0) * sampled;
}