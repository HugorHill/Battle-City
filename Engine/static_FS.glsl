#version 330 core
in vec2 texture_coord;
out vec4 color;

uniform sampler2D picture;

void main(){
  color = texture(picture,texture_coord).rgba;
}