/*
Simple pass-through vertex shader - Vertex Shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;

void main () {
	vec3 n = vertex_normal;
	vec2 t = vertex_texture;
	gl_Position = vec4(vertex_position * 0.01, 1.0);
}