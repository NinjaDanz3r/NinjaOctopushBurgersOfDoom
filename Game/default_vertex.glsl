/*
Simple pass-through vertex shader - Vertex Shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_tangent;
layout(location = 4) in vec3 vertex_bitangent;

out VertexData {
	vec3 normal;
	vec2 tex_coords;
} vertexOut;

void main () {
	vec3 tangent = vertex_tangent;
	vec3 bitangent = vertex_bitangent;
	vertexOut.normal = vertex_normal;
	vertexOut.tex_coords = vertex_texture;
	gl_Position = vec4(vertex_position, 1.0);
}