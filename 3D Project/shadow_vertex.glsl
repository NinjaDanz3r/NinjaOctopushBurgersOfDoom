/*
Shadow mapping vertex shader
*/
#version 400
layout(location = 0) in vec3 vertex_position;

uniform mat4 lightModelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;

void main () {
	vec4 pos4 = vec4(vertex_position, 1.0);
	gl_Position =  lightProjectionMatrix * lightViewMatrix *  lightModelMatrix* pos4;
}