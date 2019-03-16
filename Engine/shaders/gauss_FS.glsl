#version 330 core
in vec2 TexCoords;

uniform float radius;
uniform vec2 win_size;
uniform vec2 dir;
uniform sampler2D screenTexture;
out vec4 FragColor;

vec4 gaussian_blur(float blur)
{
	vec4 sum = vec4(0.0);
	vec2 tc = TexCoords;
	//float blur = radius/resolution; 
	float hstep = dir.x/win_size.x;
	float vstep = dir.y/win_size.y;
    
    
	sum += texture2D(screenTexture, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;
	sum += texture2D(screenTexture, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;
	sum += texture2D(screenTexture, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;
	sum += texture2D(screenTexture, vec2(tc.x - 1.0*blur*hstep, tc.y - 1.0*blur*vstep)) * 0.1945945946;
	
	sum += texture2D(screenTexture, vec2(tc.x, tc.y)) * 0.2270270270;
	
	sum += texture2D(screenTexture, vec2(tc.x + 1.0*blur*hstep, tc.y + 1.0*blur*vstep)) * 0.1945945946;
	sum += texture2D(screenTexture, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;
	sum += texture2D(screenTexture, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;
	sum += texture2D(screenTexture, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;

	return sum;
}


void main()
{
	vec4 vColor = texture(screenTexture, TexCoords.st);
    
    FragColor = vColor*gaussian_blur(radius);
}  