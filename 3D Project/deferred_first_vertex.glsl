/*
Geometry pass vertex shader (first pass)
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture;

out VertexData {
	vec2 tex_coords;
} vertexOut; 

void main () {
	vertexOut.tex_coords = vertex_texture;
	gl_Position = vec4(vertex_position, 1.0);
}