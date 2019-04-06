#version 330 core
uniform sampler2D picture;

in vec2 texture_coord;
out vec4 FragColor;

const float offset = 1.0 / 400.0;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),
        vec2( 0.0f,    offset),
        vec2( offset,  offset),
        vec2(-offset,  0.0f),
        vec2( 0.0f,    0.0f),
        vec2( offset,  0.0f),
        vec2(-offset, -offset),
        vec2( 0.0f,   -offset),
        vec2( offset, -offset)  
    );

    float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
	);
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(picture, texture_coord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    FragColor = vec4(col, 1.0);
}  