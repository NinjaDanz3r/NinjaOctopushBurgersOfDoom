/*
Simple pass-through vertex shader - Vertex Shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;

out VertexData {
	vec3 normal;
	vec2 tex_coords;
} vertexOut;

void main () {
	vertexOut.normal = vertex_normal;
	vec3 tangent = vertex_tangent;
	vertexOut.tex_coords = vertex_texture;
	gl_Position = vec4(vertex_position, 1.0);
}