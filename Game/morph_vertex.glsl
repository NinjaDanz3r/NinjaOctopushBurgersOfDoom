/*
Simple pass-through vertex shader - Vertex Shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;
layout(location = 4) in vec3 vertex_target;

uniform float tValue;

out VertexData {
	vec3 normal;
	vec3 tangent;
	vec2 tex_coords;
} vertexOut;

void main () {
	vec3 interpolated_pos = ((1-tValue)*vertex_position) + tValue*vertex_target;
	vertexOut.normal = vertex_normal;
	vertexOut.tangent = vertex_tangent;
	vertexOut.tex_coords = vertex_texture;
	gl_Position = vec4(interpolated_pos, 1.0);
}