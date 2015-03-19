/*
Shadow mapping vertex shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 vertex_tangent;

uniform mat4 lightModelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;

void main () {
	vec3 n = vertex_normal;
	vec2 t = vertex_texture;
	vec3 tangent = vertex_tangent;
	gl_Position =  lightProjectionMatrix * lightViewMatrix *  lightModelMatrix * vec4(vertex_position, 1.0);
}