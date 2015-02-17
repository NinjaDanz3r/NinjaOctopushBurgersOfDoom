/*
Geometry pass vertex shader (first pass)
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;

out VertexData {
	vec3 normal;
	vec2 tex_coords;
} vertexOut; 

void main () {
	vertexOut.normal = vertex_normal;
	vertexOut.tex_coords = vertex_texture;
	gl_Position = vec4(vertex_position, 1.0);
}