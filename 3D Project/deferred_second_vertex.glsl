/*
Basic idea of...
*/
#version 400
layout(location = 0) in vec2 in_tex_coords;

out vec2 tex_coords;

void main() {
	tex_coords = in_tex_coords;
}