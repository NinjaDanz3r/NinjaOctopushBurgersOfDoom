/*
Shadow mapping vertex shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;

uniform mat4 lightModelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;

out vec2 texCoord;

void main () {
	vec3 normal = vertex_normal;
	vec4 pos4 = vec4(vertex_position, 1.0);
	gl_Position =  lightModelMatrix * lightViewMatrix * lightProjectionMatrix * pos4;
	texCoord = vertex_texture;
}